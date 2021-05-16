using Hw2_Network;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;

namespace Hw2_Server
{
    public partial class FormMain : Form
    {
        List<MyShape> shapes;               // 그린 도형들 담아둠
        List<ToolBarButton> tbtnShapes;     // 선, 사각형, 원에 대한 버튼들
        List<ToolBarButton> tbtnLines;      // 선 스타일 버튼들

        bool isSolid;                       // 현재 선 상태
        int thick;                          // 현재 선 굵기

        public FormMain()
        {
            InitializeComponent();

            shapes = new List<MyShape>();
            tbtnShapes = new List<ToolBarButton>(new ToolBarButton[] {
                tbtnLine, tbtnRect, tbtnCircle
            });
            tbtnLines = new List<ToolBarButton>(new ToolBarButton[] {
                tbtnLine0, tbtnLine1, tbtnLine2, tbtnLine3
            });

            isSolid = true;
            thick = 1;
        }

        private void tbrTool_ButtonClick(object sender, ToolBarButtonClickEventArgs e)
        {
            if (e.Button == tbtnNew)
            {
                tbtnShapes.ForEach(tbtn => tbtn.Pushed = false);    // 모양 버튼 눌림 초기화
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
                tbtnLines.ForEach(tbtn => tbtn.Pushed = false);     // 선 스타일 버튼 눌림 초기화
                e.Button.Pushed = true;                             // 클릭한 버튼 눌림
                isSolid = e.Button != tbtnLine0;                    // 점선인지 판별
                thick =
                    e.Button == tbtnLine3 ? 5 :
                    e.Button == tbtnLine2 ? 3 : 1;                  // 선택에 따라 선 굵이 지정
            }
        }

        private void pnlPaint_MouseDown(object sender, MouseEventArgs e)
        {

        }
        private void pnlPaint_MouseMove(object sender, MouseEventArgs e)
        {

        }
        private void pnlPaint_MouseUp(object sender, MouseEventArgs e)
        {

        }
        private void pnlPaint_Paint(object sender, PaintEventArgs e)
        {

        }
    }
}
