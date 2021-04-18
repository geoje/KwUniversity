using System;
using System.Drawing;
using System.Windows.Forms;

namespace RadioAndCheck
{
    public partial class FormMain : Form
    {
        public FormMain()
        {
            InitializeComponent();
        }


        private void btnMessage_Click(object sender, EventArgs e)
        {
            MessageBox.Show(txtNote.SelectedText);
        }
        private void btnSelect_Click(object sender, EventArgs e)
        {
            txtNote.SelectAll();
            txtNote.Focus();
        }

        private void rdo_CheckedChanged(object sender, EventArgs e)
        {
            txtNote.Font = new Font((sender as RadioButton).Text,
                txtNote.Font.Size, txtNote.Font.Style);
        }
        private void chk_CheckedChanged(object sender, EventArgs e)
        {
            string style = (sender as CheckBox).Text;
            txtNote.Font = new Font(txtNote.Font.FontFamily, txtNote.Font.Size,
                (style == "Bold" ? FontStyle.Bold :
                style == "Underline" ? FontStyle.Underline :
                style == "Italic" ? FontStyle.Italic : FontStyle.Regular)
                ^ txtNote.Font.Style);
        }
    }
}
