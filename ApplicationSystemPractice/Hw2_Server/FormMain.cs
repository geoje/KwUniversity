using Hw2_Network;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using System.Windows.Forms;

namespace Hw2_Server
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
                "꽃", "새", "집", "구름", "나무", "태양", "자동차", 
            });
            r = new Random(DateTime.Now.Millisecond);
            isSolid = true;
            thick = 1;

            tbrTool.Enabled = pnlPaint.Enabled = true; // For Test
        }
        private void FormMain_Shown(object sender, EventArgs e)
        {
            listner = new TcpListener(IPAddress.Any, 4857); // 나의 전화번호
            listner.Start(1);                               // 서버 실행
            listner.BeginAcceptTcpClient(EndAccept, null);  // 클라이언트 받기 시작
        }
        private void FormMain_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (tReceive != null && tReceive.IsAlive)
                tReceive.Abort();
            listner.Stop();
        }

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
        private void pnlPaint_MouseDown(object sender, MouseEventArgs e)
        {
            if (tbtnLine.Pushed) shapes.Add(new MyLine());
            else if (tbtnRect.Pushed) shapes.Add(new MyRect());
            else if (tbtnCircle.Pushed) shapes.Add(new MyCircle());

            shapes[shapes.Count - 1].SetProperty(thick, isSolid);
            shapes[shapes.Count - 1].SetPosition(new Point(e.X, e.Y), Point.Empty);
        }
        private void pnlPaint_MouseMove(object sender, MouseEventArgs e)
        {
            if (e.Button != MouseButtons.Left) return;

            shapes[shapes.Count - 1].SetPosition(Point.Empty, new Point(e.X, e.Y));
            pnlPaint.Invalidate(true);
            pnlPaint.Update();
        }
        private void pnlPaint_Paint(object sender, PaintEventArgs e)
        {
            e.Graphics.SmoothingMode = SmoothingMode.AntiAlias;

            shapes.ForEach(s => s.Draw(e.Graphics));
        }

        /// <summary>
        /// 누군가 서버에 접속하면 실행됩니다.
        /// </summary>
        /// <param name="ar">접속한 클라이언트 정보 등 결과</param>
        private void EndAccept(IAsyncResult ar)
        {
            TcpClient client = listner.EndAcceptTcpClient(ar);      // 클라이언트 받고
            if (client.Connected)                                   // 연결 되었다면
            {
                tbrTool.Enabled = btnSend.Enabled =
                    pnlPaint.Enabled = true;                        // 컨트롤 활성화
                txtWord.Text = answer[r.Next(0, answer.Count - 1)]; // 랜덤한 제시어 표시
                (tReceive = new Thread(Receive)).Start();           // 클라로 부터 데이터 받기
            }
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

            }

            // 클라이언트와 연결이 끊기면 컨트롤들 처음 상태로 복구
            Invoke(new MethodInvoker(() =>
            {
                txtId.Text = txtWord.Text = string.Empty;
                tbrTool.Enabled = btnSend.Enabled = pnlPaint.Enabled = false;
            }));
            listner.BeginAcceptTcpClient(EndAccept, null);      // 다시 클라 접속 대기
        }
        private void Send(byte[] data)
        {
            if (client == null || !client.Connected)
                return;
        }
    }
}
