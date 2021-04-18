using System;
using System.Text.RegularExpressions;
using System.Windows.Forms;

namespace Chap04_Dialog
{
    public partial class FormMain : Form
    {
        public FormMain()
        {
            InitializeComponent();
        }

        private void txt_TextChanged(object sender, EventArgs e)
        {
            TextBox txt = sender as TextBox;
            txt.Text = Regex.Replace(txt.Text, @"\D", "");
        }
        private void btnSubmit_Click(object sender, EventArgs e)
        {
            if (MessageBox.Show(
                $"사과 {txtApple.Text}개, 바나나 {txtBanana.Text}개를 드시겠습니까?",
                "Caption",
                MessageBoxButtons.OKCancel,
                MessageBoxIcon.Question) == DialogResult.OK)
            {
                txtApple.Clear();
                txtBanana.Clear();
                MessageBox.Show("맛있냐?");
            }
        }
    }
}
