using System;
using System.Windows.Forms;

namespace Chap07_Explorer
{
    public partial class FormMain : Form
    {
        public FormMain()
        {
            InitializeComponent();
        }
        private void FormMain_Load(object sender, EventArgs e)
        {
            TreeNode root;
            string[] drives = Environment.GetLogicalDrives();
            foreach (string drive in drives)
            {
                root = trvDir.Nodes.Add(drive);
                root.ImageIndex = 2;

                if (trvDir.SelectedNode == null)
                    trvDir.SelectedNode = root;
                root.SelectedImageIndex = root.ImageIndex;
                root.Nodes.Add("");
            }
        }
    }
}
