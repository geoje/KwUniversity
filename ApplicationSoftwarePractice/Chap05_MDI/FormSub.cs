using System.Windows.Forms;

namespace Chap05_MDI
{
    public partial class FormSub : Form
    {
        public FormSub()
        {
            InitializeComponent();
        }
        public TextBox GetTextBox()
            => txtNotepad;
    }
}
