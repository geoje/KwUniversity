using CatchMind_Network;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using System.Windows.Forms;

namespace CatchMind_Server
{
    public partial class FormMain : Form
    {
        List<ToolBarButton> tbtnShapes;     // 선, 사각형, 원에 대한 버튼들
        List<ToolBarButton> tbtnLines;      // 선 스타일 버튼들
        List<MyShape> shapes;               // 그린 도형들 담아둠

        List<string> answer;                // 제시어
        Random r;                           // 제시어를 위한 랜덤
        bool isSolid;                       // 현재 선 상태
        int thick;                          // 현재 선 굵기

        TcpListener listner;                // 서버
        TcpClient client;                   // 클라이언트
        Thread tReceive;                    // 클라이언트 요청 받기
        byte[] recvBuffer, sendBuffer;      // 송수신 버퍼

        public FormMain()
        {
            InitializeComponent();

            tbtnShapes = new List<ToolBarButton>(new ToolBarButton[] {
                tbtnLine, tbtnRect, tbtnCircle
            });
            tbtnLines = new List<ToolBarButton>(new ToolBarButton[] {
                tbtnLine0, tbtnLine1, tbtnLine2, tbtnLine3
            });
            shapes = new List<MyShape>();

            answer = new List<string>(new string[]
            {
                "꽃", "새", "집", "달", "별", "밥", "눈", "비", "산", "강", "숲", "풀", "길", "칼", "총", "빵", "돈",
                "구름", "나무", "태양", "바지", "신발", "안경", "지갑", "냄비", "포도", "시계", "의자", "휴지", "리본",
                "자동차", "피아노", "컴퓨터", "모니터", "노트북", "선풍기", "셔틀콕", "세탁기", "가로등", "핸드폰"
            });
            r = new Random(DateTime.Now.Millisecond);
            isSolid = true;
            thick = 1;

            recvBuffer = new byte[Packet.BUFFER_SIZE];
            sendBuffer = new byte[Packet.BUFFER_SIZE];
        }
        /// <summary>
        /// 폼이 열리면 서버를 실행하고 비동기적으로 클라이언트 접속을 대기한다.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void FormMain_Shown(object sender, EventArgs e)
        {
            listner = new TcpListener(IPAddress.Any, 4857); // 나의 전화번호
            listner.Start();                                // 서버 실행
            listner.BeginAcceptTcpClient(EndAccept, null);  // 클라이언트 받기 시작
        }
        /// <summary>
        /// 폼이 닫힐 때 수신 대기하던 스레드를 종료하고 클라이언트와 연결된 소켓을 닫아서 서버 종료를 알린다.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void FormMain_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (tReceive != null && tReceive.IsAlive)
                tReceive.Abort();
            listner.Stop();
        }

        /// <summary>
        /// 툴바 버튼들이 클릭 될 경우 버튼에 따라 팬를 교체한다.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void tbrTool_ButtonClick(object sender, ToolBarButtonClickEventArgs e)
        {
            if (e.Button == tbtnNew)
            {
                shapes.Clear();                                     // 모든 도형 초기화
                pnlPaint.Refresh();                                 // 패널 갱신
            }
            else if (tbtnShapes.Exists(tbtn => tbtn == e.Button))   // 모양 버튼을 누른 경우
            {
                tbtnShapes.ForEach(tbtn => tbtn.Pushed = false);    // 모양 버튼 눌림 초기화
                e.Button.Pushed = true;                             // 클릭한 버튼 눌림
            }
            else if (tbtnLines.Exists(tbtn => tbtn == e.Button))
            {
                tbtnLines.ForEach(tbtn => tbtn.Pushed = false);     // 스타일 버튼 눌림 초기화
                e.Button.Pushed = true;                             // 클릭한 버튼 눌림
                isSolid = e.Button != tbtnLine0;                    // 점선인지 판별
                thick =
                    e.Button == tbtnLine3 ? 5 :
                    e.Button == tbtnLine2 ? 3 : 1;                  // 선택에 따라 선 스타일 지정
            }
        }
        /// <summary>
        /// 패널에서 마우스를 누르면 툴바에서 선택된 도형 1개를 만들고 리스트에 추가한다.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void pnlPaint_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button != MouseButtons.Left) return;

            if (tbtnLine.Pushed) shapes.Add(new MyLine());
            else if (tbtnRect.Pushed) shapes.Add(new MyRect());
            else if (tbtnCircle.Pushed) shapes.Add(new MyCircle());

            shapes[shapes.Count - 1].SetProperty(thick, isSolid);
            shapes[shapes.Count - 1].SetPosition(new Point(e.X, e.Y), Point.Empty);
        }
        /// <summary>
        /// 패널에서 마우스를 움직이면 누를 때 추가된 도형의 모양을 마우스에 맞게 변형한다.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void pnlPaint_MouseMove(object sender, MouseEventArgs e)
        {
            if (e.Button != MouseButtons.Left) return;  // 마우스가 움직일 때 왼쪽 버튼이 누르는 중이 아니면 코드를 실행하지 않는다.

            // 도형 리스트의 마지막 객체 모양을 변형하는데 마지막 객체는 누를때 추가된 것이므로 마치 그리는 것 처럼 표현 된다.
            shapes[shapes.Count - 1].SetPosition(Point.Empty, new Point(e.X, e.Y));
            pnlPaint.Invalidate(true);  // 이건 뭐지
            pnlPaint.Update();          // 패널 갱신
        }
        /// <summary>
        /// 직접 그린 도형들을 패널에 모두 표시한다.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void pnlPaint_Paint(object sender, PaintEventArgs e)
        {
            e.Graphics.SmoothingMode = SmoothingMode.AntiAlias;

            shapes.ForEach(s => s.Draw(e.Graphics));
        }
        /// <summary>
        /// 클라이언트한테 직접 그린 도형들을 전송한다.
        /// 여러번 보내도 클아이언트 측에선 곂쳐서 보이지 않고 서버에서 보이는 화면 딱 그대로 보인다.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnSend_Click(object sender, EventArgs e)
        {
            Send(new ShapePacket(shapes));
        }

        /// <summary>
        /// 누군가 서버에 접속하면 실행됩니다.
        /// </summary>
        /// <param name="ar">접속한 클라이언트 정보 등 결과</param>
        private void EndAccept(IAsyncResult ar)
        {
            try
            {
                client = listner.EndAcceptTcpClient(ar);      // 클라이언트 받고
            }
            catch
            {
                return;
            }
            if (client.Connected)                                   // 연결 되었다면
                (tReceive = new Thread(Receive)).Start();           // 클라로 부터 데이터 받기
            else
                listner.BeginAcceptTcpClient(EndAccept, null);      // 아니라면 다시 클라 접속 대기

        }
        /// <summary>
        /// 클라이언트와 정상 연결 되었다면 데이터를 받기위해 실행됩니다.
        /// </summary>
        private void Receive()
        {
            while (client.Connected)    // 클라이언트 연결이 정상이면 계속 데이터 받기
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
                if (packet == null) break;

                // 패킷 타입에 따라 진행
                if (packet.Type == PacketType.Login)
                {
                    Invoke(new MethodInvoker(() =>
                    {
                        // 클라이언트 아이디 표시
                        txtId.Text = (packet as LoginPacket).id;
                        // 컨트롤 활성화
                        tbrTool.Enabled = btnSend.Enabled = pnlPaint.Enabled = true;
                        // 랜덤한 제시어 표시
                        txtWord.Text = answer[r.Next(0, answer.Count - 1)];
                    }));
                }
                else if (packet.Type == PacketType.Answer)
                {
                    if (txtWord.Text ==
                        (packet as AnswerPacket).answer)
                    {
                        Send(new AnswerPacket(true));       // 성공을 클라에게 전송
                        Invoke(new MethodInvoker(() =>
                        {
                            shapes.Clear();                 // 모든 도형을 지우고
                            pnlPaint.Refresh();             // 화면 갱신
                            txtWord.Text = answer[r.Next(0, answer.Count - 1)];     // 랜덤한 제시어 표시
                        }));
                    }
                    else
                        Send(new AnswerPacket(false));      // 실패를 전송
                }
            }

            // 클라이언트와 연결이 끊기면 컨트롤들 처음 상태로 복구
            Invoke(new MethodInvoker(() =>
            {
                shapes.Clear();
                pnlPaint.Refresh();
                txtId.Text = txtWord.Text = string.Empty;
                tbrTool.Enabled = btnSend.Enabled = pnlPaint.Enabled = false;
            }));
            listner.BeginAcceptTcpClient(EndAccept, null);      // 다시 클라 접속 대기
        }
        /// <summary>
        /// 클라이언트와 연결된 소켓을 통해 패킷을 직렬화 한 뒤 전송한다.
        /// </summary>
        /// <param name="packet"></param>
        private void Send(Packet packet)
        {
            Array.Clear(sendBuffer, 0, sendBuffer.Length);  // 송신 버퍼를 비우고
            try
            {
                packet.Serialize().CopyTo(sendBuffer, 0);       // 패킷을 직렬화 하고
                client.GetStream().Write(sendBuffer, 0, sendBuffer.Length); // 송신 버퍼에 복사하고 전송
            }
            catch
            {
                MessageBox.Show("너무 많은 도형을 보낼 수 없습니다.", "전송 오류", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
    }
}
