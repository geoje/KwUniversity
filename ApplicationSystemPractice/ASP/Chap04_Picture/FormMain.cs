using System;
using System.Windows.Forms;

namespace Chap04_Picture
{
    public partial class FormMain : Form
    {
        public FormMain()
        {
            InitializeComponent();
        }

        private void btnChange_Click(object sender, EventArgs e)
        {
            picProfile.ImageLocation = txtUrl.Text;
        }
        private void rdo_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton rdo = sender as RadioButton;
            picProfile.SizeMode =
                rdo == rdoNormal ? PictureBoxSizeMode.Normal :
                rdo == rdoStretchImage ? PictureBoxSizeMode.StretchImage :
                rdo == rdoAutoSize ? PictureBoxSizeMode.AutoSize :
                rdo == rdoCenterImage ? PictureBoxSizeMode.CenterImage :
                rdo == rdoZoom ? PictureBoxSizeMode.Zoom :
                PictureBoxSizeMode.Normal;
        }

        private void chkVisible_CheckedChanged(object sender, EventArgs e)
        {
            picProfile.Visible = chkVisible.Checked;
        }
    }
}
