using System;
using System.Drawing;
using System.Windows.Forms;

namespace Chap07_Modaless
{
    public partial class FormColor : Form
    {
        public event EventHandler Changed;

        public FormColor()
        {
            InitializeComponent();
        }

        private void hsb_Scroll(object sender, ScrollEventArgs e)
        {
            btnApply.Enabled = true;
            BackColor = Color.FromArgb(hsbRed.Value, hsbGreen.Value, hsbBlue.Value);
        }
        private void btnOK_Click(object sender, EventArgs e)
        {
            if (btnApply.Enabled) btnApply.PerformClick();
            Close();
        }
        private void btnApply_Click(object sender, EventArgs e)
        {
            if (Changed != null)
                Changed(this, new EventArgs());
        }
        private void btnCancel_Click(object sender, EventArgs e)
        {
            Close();
        }
    }
}
