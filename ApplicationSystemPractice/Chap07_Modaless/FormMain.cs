using System;
using System.Windows.Forms;

namespace Chap07_Modaless
{
    public partial class FormMain : Form
    {
        public FormMain()
        {
            InitializeComponent();
        }

        private void btnShow_Click(object sender, EventArgs e)
        {
            FormColor fc = new FormColor();
            fc.Owner = this;
            fc.Changed += Fc_Changed;
            fc.Show();
        }

        private void Fc_Changed(object sender, EventArgs e)
            => BackColor = (sender as Form).BackColor;
    }
}
