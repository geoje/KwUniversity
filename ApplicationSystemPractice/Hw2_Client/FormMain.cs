using Hw2_Network;
using System;
using System.Collections.Generic;
using System.Drawing.Drawing2D;
using System.Net.Sockets;
using System.Threading;
using System.Windows.Forms;

namespace Hw2_Client
{
    public partial class FormMain : Form
    {
        List<MyShape> shapes;               // 서버에서 받은 도형들 담아둠

        TcpClient client;                   // 서버와 연결된 소켓
        Thread tReceive;                    // 서버 수신 받기
        byte[] recvBuffer, sendBuffer;      // 송수신 버퍼

        public FormMain()
        {
            InitializeComponent();

            shapes = new List<MyShape>();
            client = new TcpClient();
            recvBuffer = new byte[Packet.BUFFER_SIZE];
            sendBuffer = new byte[Packet.BUFFER_SIZE];
        }
        private void FormMain_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (tReceive != null && tReceive.IsAlive)
                tReceive.Abort();
            client.Close();
        }

        private void pnlPaint_Paint(object sender, PaintEventArgs e)
        {
            e.Graphics.SmoothingMode = SmoothingMode.AntiAlias;

            shapes.ForEach(s => s.Draw(e.Graphics));
        }
        private void btnConnect_Click(object sender, EventArgs e)
        {
            lblIp.Enabled = txtIp.Enabled = btnConnect.Enabled = false;
            client.BeginConnect(txtIp.Text, 4857, EndConnect, null);
        }
        private void btnLogin_Click(object sender, EventArgs e)
        {
            Send(new LoginPacket(txtId.Text));
            lblId.Enabled = txtId.Enabled = btnLogin.Enabled = false;
            lblAnswer.Enabled = txtAnswer.Enabled = btnSend.Enabled = true;
        }
        private void btnSend_Click(object sender, EventArgs e)
        {
            Send(new AnswerPacket(txtAnswer.Text));
        }

        private void EndConnect(IAsyncResult ar)
        {
            Invoke(new MethodInvoker(() =>
            {
                if (client.Connected)
                {
                    lblId.Enabled = txtId.Enabled = btnLogin.Enabled = true;
                    (tReceive = new Thread(Receive)).Start();           // 클라로 부터 데이터 받기
                }
                else
                    lblIp.Enabled = txtIp.Enabled = btnConnect.Enabled = true;
            }));
        }
        private void Receive()
        {
            while (client.Connected)    // 서버와 연결이 정상이면 계속 데이터 받기
            {
                Array.Clear(recvBuffer, 0, recvBuffer.Length);
                try
                {
                    client.GetStream().Read(recvBuffer, 0, recvBuffer.Length);
                }
                catch
                {
                    break;
                }
                Packet packet = Packet.Deserialize(recvBuffer);

                // 패킷 타입에 따라 진행
                if (packet.Type == PacketType.Shape)
                {
                    shapes = (packet as ShapePacket).shapes;    // 도형 받고
                    Invoke(new MethodInvoker(() =>
                    {
                        pnlPaint.Refresh();     // 화면 갱신
                    }));
                }
                else if (packet.Type == PacketType.Answer)
                {
                    if ((packet as AnswerPacket).success)
                    {
                        MessageBox.Show("맞았습니다.\n잠시 기다렸다가 다음 문제를 맞춰보세요.");
                        Invoke(new MethodInvoker(() =>
                        {
                            shapes.Clear();         // 모든 도형을 지우고
                            pnlPaint.Refresh();     // 화면 갱신
                        }));
                    }
                    else
                        MessageBox.Show("틀렸습니다.");
                }
            }

            // 서버와 연결이 끊기면 컨트롤들 처음 상태로 복구
            Invoke(new MethodInvoker(() =>
            {
                shapes.Clear();
                pnlPaint.Refresh();

                lblId.Enabled = txtId.Enabled = btnLogin.Enabled =
                    lblAnswer.Enabled = txtAnswer.Enabled = btnSend.Enabled = false;
                lblIp.Enabled = txtIp.Enabled = btnConnect.Enabled = true;
                txtIp.Text = txtId.Text = txtAnswer.Text = "";
            }));

            client.Close();
            client = new TcpClient();
        }

        private void Send(Packet packet)
        {
            Array.Clear(sendBuffer, 0, sendBuffer.Length);  // 송신 버퍼를 비우고
            packet.Serialize().CopyTo(sendBuffer, 0);       // 패킷을 직렬화 하고
            client.GetStream().Write(sendBuffer, 0, sendBuffer.Length); // 송신 버퍼에 복사하고 전송
        }
    }
}
