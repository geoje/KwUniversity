using System;
using System.IO;
using System.Windows.Forms;

namespace Chap05_MDI
{
    public partial class FormMain : Form
    {
        FormSub child;
        int nChild;

        public FormMain()
        {
            InitializeComponent();
            sfd.InitialDirectory = ofd.InitialDirectory =
                Environment.GetFolderPath(Environment.SpecialFolder.Desktop);
            sfd.Filter = ofd.Filter =
                "Text (*.txt)|*.txt|" +
                "All Files (*.*)|*.*";
        }
        private void FormMain_Shown(object sender, EventArgs e)
        {
            //try
            //{
            //    RegistryKey rk = Registry.CurrentUser.OpenSubKey(@"C# Notepad\Notepad");

            //    txtNotepad.Font = fnd.Font = new Font(
            //        Convert.ToString(rk.GetValue("FontName")),
            //        Convert.ToSingle(rk.GetValue("FontSize")));
            //    txtNotepad.ForeColor = Color.FromArgb(
            //        Convert.ToInt32(rk.GetValue("ForeColor")));
            //    txtNotepad.BackColor = Color.FromArgb(
            //        Convert.ToInt32(rk.GetValue("BackColor")));
            //}
            //catch (Exception) { }
        }
        private void FormMain_FormClosing(object sender, FormClosingEventArgs e)
        {
            //try
            //{
            //    RegistryKey rk = Registry.CurrentUser.CreateSubKey(@"C# Notepad\Notepad");

            //    rk.SetValue("FontName", txtNotepad.Font.FontFamily.GetName(0));
            //    rk.SetValue("FontSize", txtNotepad.Font.Size.ToString());
            //    rk.SetValue("ForeColor", txtNotepad.ForeColor.ToArgb());
            //    rk.SetValue("BackColor", txtNotepad.BackColor.ToArgb());
            //}
            //catch (Exception) { }
        }

        // 파일
        private void tsmiNew_Click(object sender, EventArgs e)
        {
            child = new FormSub();
            child.MdiParent = this;
            child.Text = "NONAME" + nChild++;
            child.Show();
        }
        private void tsmiOpen_Click(object sender, EventArgs e)
        {
            if (ofd.ShowDialog() != DialogResult.OK) return;

            using (StreamReader sr = new StreamReader(ofd.OpenFile()))
            {
                tsmiNew.PerformClick();
                child.GetTextBox().Text = sr.ReadToEnd();
                child.Text = ofd.FileName;
            }
        }
        private void tsmiSave_Click(object sender, EventArgs e)
        {
            if (sfd.ShowDialog() != DialogResult.OK) return;

            child = (FormSub)ActiveMdiChild;
            using (StreamWriter sw = new StreamWriter(child.Text))
                sw.Write(child.GetTextBox().Text);
        }
        private void tsmiSaveAs_Click(object sender, EventArgs e)
        {
            tsmiSave.PerformClick();
            child.Text = sfd.FileName;
        }
        private void tsmiExit_Click(object sender, EventArgs e)
        {
            Close();
        }

        // 편집
        private void tsmiUndo_Click(object sender, EventArgs e)
            => ((FormSub)ActiveMdiChild).GetTextBox().Undo();
        private void tsmiCut_Click(object sender, EventArgs e)
            => ((FormSub)ActiveMdiChild).GetTextBox().Cut();
        private void tsmiCopy_Click(object sender, EventArgs e)
            => ((FormSub)ActiveMdiChild).GetTextBox().Copy();
        private void tsmiPaste_Click(object sender, EventArgs e)
            => ((FormSub)ActiveMdiChild).GetTextBox().Paste();
        private void tsmiDelete_Click(object sender, EventArgs e)
            => ((FormSub)ActiveMdiChild).GetTextBox().SelectedText = "";
        private void tsmiSelectAll_Click(object sender, EventArgs e)
            => ((FormSub)ActiveMdiChild).GetTextBox().SelectAll();

        // 서식
        private void tsmiWordWrap_Click(object sender, EventArgs e)
            => ((FormSub)ActiveMdiChild).GetTextBox().WordWrap = tsmiWordWrap.Checked = !tsmiWordWrap.Checked;
        private void tsmiFont_Click(object sender, EventArgs e)
        {
            if (fnd.ShowDialog() == DialogResult.OK)
                ((FormSub)ActiveMdiChild).GetTextBox().Font = fnd.Font;
        }
        private void tsmiFontColor_Click(object sender, EventArgs e)
        {
            if (cld.ShowDialog() == DialogResult.OK)
                ((FormSub)ActiveMdiChild).GetTextBox().ForeColor = cld.Color;
        }
        private void tsmiBackColor_Click(object sender, EventArgs e)
        {
            if (cld.ShowDialog() == DialogResult.OK)
                ((FormSub)ActiveMdiChild).GetTextBox().BackColor = cld.Color;
        }
    }
}
