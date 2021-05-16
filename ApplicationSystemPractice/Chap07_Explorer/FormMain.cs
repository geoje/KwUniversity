using System;
using System.Diagnostics;
using System.IO;
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
                root.Nodes.Add(""); // 확장 버튼을 위해
            }
        }

        private void trvDir_BeforeExpand(object sender, TreeViewCancelEventArgs e)
        {
            try
            {
                e.Node.Nodes.Clear();
                DirectoryInfo[] dirs = new DirectoryInfo(e.Node.FullPath).GetDirectories();

                foreach (DirectoryInfo dir in dirs)
                {
                    TreeNode node = e.Node.Nodes.Add(dir.Name);
                    setPlus(node);
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
        private void trvDir_AfterSelect(object sender, TreeViewEventArgs e)
        {
            try
            {
                DirectoryInfo mainDir = new DirectoryInfo(e.Node.FullPath);
                txtPath.Text = e.Node.FullPath.Remove(2, 1);
                lvwFile.Items.Clear(); // 기존 정보 초기화

                // 디렉토리
                DirectoryInfo[] dirs = mainDir.GetDirectories();
                foreach (DirectoryInfo dir in dirs)
                {
                    ListViewItem item = lvwFile.Items.Add(dir.Name);
                    item.SubItems.Add("");
                    item.SubItems.Add(dir.LastWriteTime.ToString());
                    item.ImageIndex = 0;
                    item.Tag = "D";
                }

                // 파일
                FileInfo[] files = mainDir.GetFiles();
                foreach (FileInfo file in files)
                {
                    ListViewItem item = lvwFile.Items.Add(file.Name);
                    item.SubItems.Add(file.Length.ToString());
                    item.SubItems.Add(file.LastWriteTime.ToString());
                    item.ImageIndex = 1;
                    item.Tag = "F";
                }
                lvwFile.AutoResizeColumns(ColumnHeaderAutoResizeStyle.ColumnContent);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
        private void lvwFile_DoubleClick(object sender, EventArgs e)
            => OpenFiles();
        private void mnuOpen_Click(object sender, EventArgs e)
            => OpenFiles();

        public void setPlus(TreeNode node)
        {
            try
            {
                if (new DirectoryInfo(node.FullPath).GetDirectories().Length > 0)
                    node.Nodes.Add("");
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
        public void OpenFiles()
        {
            foreach (ListViewItem item in lvwFile.SelectedItems)
                OpenItem(item);
        }
        public void OpenItem(ListViewItem item)
        {
            if (item.Tag.ToString() == "D")
            {
                TreeNode node = trvDir.SelectedNode;
                node.Expand();
                TreeNode child = node.FirstNode;

                while (child != null)
                {
                    if (child.Text == item.Text)
                    {
                        trvDir.SelectedNode = child;
                        trvDir.Focus();
                    }
                    child = child.NextNode;
                }
            }
            else
                Process.Start(txtPath.Text + @"\" + item.Text);
        }

        private void mnu_Click(object sender, EventArgs e)
        {
            ToolStripMenuItem item = sender as ToolStripMenuItem;
            mnuDetail.Checked =
                mnuList.Checked =
                mnuSmall.Checked =
                mnuLarge.Checked = false;

            switch (item.Text)
            {
                case "자세히":
                    mnuDetail.Checked = true;
                    lvwFile.View = View.Details;
                    lvwFile.AutoResizeColumns(ColumnHeaderAutoResizeStyle.ColumnContent);
                    break;
                case "간단히":
                    mnuList.Checked = true;
                    lvwFile.View = View.List;
                    break;
                case "작은 아이콘":
                    mnuSmall.Checked = true;
                    lvwFile.View = View.SmallIcon;
                    break;
                case "큰 아이콘":
                    mnuLarge.Checked = true;
                    lvwFile.View = View.LargeIcon;
                    break;
            }
        }
    }
}
