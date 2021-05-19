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
        /// <summary>
        /// 폼이 닫힐 때 수신 대기하던 스레드를 종료하고 서버와 연결된 소켓을 닫아서 접속 종료를 알린다.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void FormMain_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (tReceive != null && tReceive.IsAlive)
                tReceive.Abort();
            client.Close();
        }

        /// <summary>
        /// 서버에서 받은 도형들을 모두 그린다.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void pnlPaint_Paint(object sender, PaintEventArgs e)
        {
            e.Graphics.SmoothingMode = SmoothingMode.AntiAlias;

            shapes.ForEach(s => s.Draw(e.Graphics));
        }
        /// <summary>
        /// 접속 버튼 클릭 시 접속 관련 컨트롤을 비활성화 하고 서버에 접속을 시도한다.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnConnect_Click(object sender, EventArgs e)
        {
            lblIp.Enabled = txtIp.Enabled = btnConnect.Enabled = false;
            client.BeginConnect(txtIp.Text, 4857, EndConnect, null);
        }
        /// <summary>
        /// 입력한 아이디로 로그인을 시도하는데 만약 비어있을 경우 로그인을 시도하지 않고 오류 메세지를 출력한다.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnLogin_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(txtId.Text))
            {
                MessageBox.Show("아이디를 입력해주세요", "로그인 오류", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            Send(new LoginPacket(txtId.Text));
            lblId.Enabled = txtId.Enabled = btnLogin.Enabled = false;
            lblAnswer.Enabled = txtAnswer.Enabled = btnSend.Enabled = true;
        }
        /// <summary>
        /// 정답을 제출한다.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnSend_Click(object sender, EventArgs e)
        {
            Send(new AnswerPacket(txtAnswer.Text));
        }

        /// <summary>
        /// 비동기적으로 시도한 접속이 끝나면 호출 된다.
        /// 정상적으로 로그인 되었는지 체크 후 패킷 수신을 시작한다.
        /// </summary>
        /// <param name="ar"></param>
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
        /// <summary>
        /// 패킷을 수신하여 상황에 맞게 진행하며 스레드에 의해 독립적으로 동작될 것이다.
        /// </summary>
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
        /// <summary>
        /// 서버와 연결된 소켓을 통해 패킷을 직렬화 한 뒤 전송한다.
        /// </summary>
        /// <param name="packet"></param>
        private void Send(Packet packet)
        {
            Array.Clear(sendBuffer, 0, sendBuffer.Length);  // 송신 버퍼를 비우고
            packet.Serialize().CopyTo(sendBuffer, 0);       // 패킷을 직렬화 하고
            client.GetStream().Write(sendBuffer, 0, sendBuffer.Length); // 송신 버퍼에 복사하고 전송
        }
    }
}
