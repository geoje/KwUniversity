using Microsoft.Win32;
using System;
using System.Drawing;
using System.IO;
using System.Windows.Forms;

namespace Chap04_MenuStrip
{
    public partial class FormMain : Form
    {
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
            try
            {
                RegistryKey rk = Registry.CurrentUser.OpenSubKey(@"C# Notepad\Notepad");

                txtNotepad.Font = fnd.Font = new Font(
                    Convert.ToString(rk.GetValue("FontName")),
                    Convert.ToSingle(rk.GetValue("FontSize")));
                txtNotepad.ForeColor = Color.FromArgb(
                    Convert.ToInt32(rk.GetValue("ForeColor")));
                txtNotepad.BackColor = Color.FromArgb(
                    Convert.ToInt32(rk.GetValue("BackColor")));
            }
            catch (Exception) { }
        }
        private void FormMain_FormClosing(object sender, FormClosingEventArgs e)
        {
            try
            {
                RegistryKey rk = Registry.CurrentUser.CreateSubKey(@"C# Notepad\Notepad");

                rk.SetValue("FontName", txtNotepad.Font.FontFamily.GetName(0));
                rk.SetValue("FontSize", txtNotepad.Font.Size.ToString());
                rk.SetValue("ForeColor", txtNotepad.ForeColor.ToArgb());
                rk.SetValue("BackColor", txtNotepad.BackColor.ToArgb());
            }
            catch (Exception) { }
        }

        // 파일
        private void tsmiNew_Click(object sender, EventArgs e)
        {
            Text = "Notepad";
            txtNotepad.Text = "";
        }
        private void tsmiOpen_Click(object sender, EventArgs e)
        {
            if (ofd.ShowDialog() != DialogResult.OK) return;

            using (StreamReader sr = new StreamReader(ofd.OpenFile()))
                txtNotepad.Text = sr.ReadToEnd();
            Text = Path.GetFileName(ofd.FileName);
        }
        private void tsmiSave_Click(object sender, EventArgs e)
        {
            if (ofd.FileName == "")
            {
                tsmiSaveAs.PerformClick();
                return;
            }
            sfd.FileName = ofd.FileName;

            using (StreamWriter sw = new StreamWriter(sfd.OpenFile()))
                sw.Write(txtNotepad.Text);
            Text = Path.GetFileName(sfd.FileName);
        }
        private void tsmiSaveAs_Click(object sender, EventArgs e)
        {
            if (sfd.ShowDialog() != DialogResult.OK) return;

            ofd.FileName = sfd.FileName;
            tsmiSave.PerformClick();
        }
        private void tsmiExit_Click(object sender, EventArgs e)
        {
            Close();
        }

        // 편집
        private void tsmiUndo_Click(object sender, EventArgs e)
            => txtNotepad.Undo();
        private void tsmiCut_Click(object sender, EventArgs e)
            => txtNotepad.Cut();
        private void tsmiCopy_Click(object sender, EventArgs e)
            => txtNotepad.Copy();
        private void tsmiPaste_Click(object sender, EventArgs e)
            => txtNotepad.Paste();
        private void tsmiDelete_Click(object sender, EventArgs e)
            => txtNotepad.SelectedText = "";
        private void tsmiSelectAll_Click(object sender, EventArgs e)
            => txtNotepad.SelectAll();

        // 서식
        private void tsmiWordWrap_Click(object sender, EventArgs e)
            => txtNotepad.WordWrap = tsmiWordWrap.Checked = !tsmiWordWrap.Checked;
        private void tsmiFont_Click(object sender, EventArgs e)
        {
            if (fnd.ShowDialog() == DialogResult.OK)
                txtNotepad.Font = fnd.Font;
        }
        private void tsmiFontColor_Click(object sender, EventArgs e)
        {
            if (cld.ShowDialog() == DialogResult.OK)
                txtNotepad.ForeColor = cld.Color;
        }
        private void tsmiBackColor_Click(object sender, EventArgs e)
        {
            if (cld.ShowDialog() == DialogResult.OK)
                txtNotepad.BackColor = cld.Color;
        }
    }
}
