using Hw2_Network;
using System;
using System.Collections.Generic;
using System.Drawing.Drawing2D;
using System.Net.Sockets;
using System.Windows.Forms;

namespace Hw2_Client
{
    public partial class FormMain : Form
    {
        List<MyShape> shapes;               // 서버에서 받은 도형들 담아둠

        TcpClient client;

        public FormMain()
        {
            InitializeComponent();

            shapes = new List<MyShape>();
        }

        private void pnlPaint_Paint(object sender, PaintEventArgs e)
        {
            e.Graphics.SmoothingMode = SmoothingMode.AntiAlias;

            shapes.ForEach(s => s.Draw(e.Graphics));
        }

        private void btnConnect_Click(object sender, EventArgs e)
        {

        }
        private void btnLogin_Click(object sender, EventArgs e)
        {

        }

        private void Receive()
        {

        }
        private void Send(byte[] data)
        {

        }
    }
}
