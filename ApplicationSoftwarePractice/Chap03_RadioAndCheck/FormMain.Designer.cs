
namespace RadioAndCheck
{
    partial class FormMain
    {
        /// <summary>
        /// 필수 디자이너 변수입니다.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 사용 중인 모든 리소스를 정리합니다.
        /// </summary>
        /// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 디자이너에서 생성한 코드

        /// <summary>
        /// 디자이너 지원에 필요한 메서드입니다. 
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마세요.
        /// </summary>
        private void InitializeComponent()
        {
            this.txtNote = new System.Windows.Forms.TextBox();
            this.btnMessage = new System.Windows.Forms.Button();
            this.btnSelect = new System.Windows.Forms.Button();
            this.grpFonts = new System.Windows.Forms.GroupBox();
            this.grpStyles = new System.Windows.Forms.GroupBox();
            this.rdoDotum = new System.Windows.Forms.RadioButton();
            this.rdoGulim = new System.Windows.Forms.RadioButton();
            this.rdoGungsuh = new System.Windows.Forms.RadioButton();
            this.chkBold = new System.Windows.Forms.CheckBox();
            this.chkUnderline = new System.Windows.Forms.CheckBox();
            this.chkItalic = new System.Windows.Forms.CheckBox();
            this.grpFonts.SuspendLayout();
            this.grpStyles.SuspendLayout();
            this.SuspendLayout();
            // 
            // txtNote
            // 
            this.txtNote.Location = new System.Drawing.Point(12, 12);
            this.txtNote.Multiline = true;
            this.txtNote.Name = "txtNote";
            this.txtNote.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.txtNote.Size = new System.Drawing.Size(279, 160);
            this.txtNote.TabIndex = 0;
            this.txtNote.WordWrap = false;
            // 
            // btnMessage
            // 
            this.btnMessage.Location = new System.Drawing.Point(297, 12);
            this.btnMessage.Name = "btnMessage";
            this.btnMessage.Size = new System.Drawing.Size(75, 23);
            this.btnMessage.TabIndex = 1;
            this.btnMessage.Text = "Message";
            this.btnMessage.UseVisualStyleBackColor = true;
            this.btnMessage.Click += new System.EventHandler(this.btnMessage_Click);
            // 
            // btnSelect
            // 
            this.btnSelect.Location = new System.Drawing.Point(297, 149);
            this.btnSelect.Name = "btnSelect";
            this.btnSelect.Size = new System.Drawing.Size(75, 23);
            this.btnSelect.TabIndex = 1;
            this.btnSelect.Text = "Select";
            this.btnSelect.UseVisualStyleBackColor = true;
            this.btnSelect.Click += new System.EventHandler(this.btnSelect_Click);
            // 
            // grpFonts
            // 
            this.grpFonts.Controls.Add(this.rdoGungsuh);
            this.grpFonts.Controls.Add(this.rdoGulim);
            this.grpFonts.Controls.Add(this.rdoDotum);
            this.grpFonts.Location = new System.Drawing.Point(12, 178);
            this.grpFonts.Name = "grpFonts";
            this.grpFonts.Size = new System.Drawing.Size(177, 171);
            this.grpFonts.TabIndex = 2;
            this.grpFonts.TabStop = false;
            this.grpFonts.Text = "Fonts";
            // 
            // grpStyles
            // 
            this.grpStyles.Controls.Add(this.chkItalic);
            this.grpStyles.Controls.Add(this.chkUnderline);
            this.grpStyles.Controls.Add(this.chkBold);
            this.grpStyles.Location = new System.Drawing.Point(195, 178);
            this.grpStyles.Name = "grpStyles";
            this.grpStyles.Size = new System.Drawing.Size(177, 171);
            this.grpStyles.TabIndex = 2;
            this.grpStyles.TabStop = false;
            this.grpStyles.Text = "Styles";
            // 
            // rdoDotum
            // 
            this.rdoDotum.AutoSize = true;
            this.rdoDotum.Location = new System.Drawing.Point(6, 20);
            this.rdoDotum.Name = "rdoDotum";
            this.rdoDotum.Size = new System.Drawing.Size(47, 16);
            this.rdoDotum.TabIndex = 0;
            this.rdoDotum.TabStop = true;
            this.rdoDotum.Text = "돋움";
            this.rdoDotum.UseVisualStyleBackColor = true;
            this.rdoDotum.CheckedChanged += new System.EventHandler(this.rdo_CheckedChanged);
            // 
            // rdoGulim
            // 
            this.rdoGulim.AutoSize = true;
            this.rdoGulim.Location = new System.Drawing.Point(6, 42);
            this.rdoGulim.Name = "rdoGulim";
            this.rdoGulim.Size = new System.Drawing.Size(47, 16);
            this.rdoGulim.TabIndex = 0;
            this.rdoGulim.TabStop = true;
            this.rdoGulim.Text = "굴림";
            this.rdoGulim.UseVisualStyleBackColor = true;
            this.rdoGulim.CheckedChanged += new System.EventHandler(this.rdo_CheckedChanged);
            // 
            // rdoGungsuh
            // 
            this.rdoGungsuh.AutoSize = true;
            this.rdoGungsuh.Location = new System.Drawing.Point(6, 64);
            this.rdoGungsuh.Name = "rdoGungsuh";
            this.rdoGungsuh.Size = new System.Drawing.Size(47, 16);
            this.rdoGungsuh.TabIndex = 0;
            this.rdoGungsuh.TabStop = true;
            this.rdoGungsuh.Text = "궁서";
            this.rdoGungsuh.UseVisualStyleBackColor = true;
            this.rdoGungsuh.CheckedChanged += new System.EventHandler(this.rdo_CheckedChanged);
            // 
            // chkBold
            // 
            this.chkBold.AutoSize = true;
            this.chkBold.Location = new System.Drawing.Point(6, 21);
            this.chkBold.Name = "chkBold";
            this.chkBold.Size = new System.Drawing.Size(49, 16);
            this.chkBold.TabIndex = 0;
            this.chkBold.Text = "Bold";
            this.chkBold.UseVisualStyleBackColor = true;
            this.chkBold.CheckedChanged += new System.EventHandler(this.chk_CheckedChanged);
            // 
            // chkUnderline
            // 
            this.chkUnderline.AutoSize = true;
            this.chkUnderline.Location = new System.Drawing.Point(6, 42);
            this.chkUnderline.Name = "chkUnderline";
            this.chkUnderline.Size = new System.Drawing.Size(77, 16);
            this.chkUnderline.TabIndex = 0;
            this.chkUnderline.Text = "Underline";
            this.chkUnderline.UseVisualStyleBackColor = true;
            this.chkUnderline.CheckedChanged += new System.EventHandler(this.chk_CheckedChanged);
            // 
            // chkItalic
            // 
            this.chkItalic.AutoSize = true;
            this.chkItalic.Location = new System.Drawing.Point(6, 65);
            this.chkItalic.Name = "chkItalic";
            this.chkItalic.Size = new System.Drawing.Size(50, 16);
            this.chkItalic.TabIndex = 0;
            this.chkItalic.Text = "Italic";
            this.chkItalic.UseVisualStyleBackColor = true;
            this.chkItalic.CheckedChanged += new System.EventHandler(this.chk_CheckedChanged);
            // 
            // FormMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(384, 361);
            this.Controls.Add(this.grpStyles);
            this.Controls.Add(this.grpFonts);
            this.Controls.Add(this.btnSelect);
            this.Controls.Add(this.btnMessage);
            this.Controls.Add(this.txtNote);
            this.Name = "FormMain";
            this.Text = "RadioAndCheck";
            this.grpFonts.ResumeLayout(false);
            this.grpFonts.PerformLayout();
            this.grpStyles.ResumeLayout(false);
            this.grpStyles.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox txtNote;
        private System.Windows.Forms.Button btnMessage;
        private System.Windows.Forms.Button btnSelect;
        private System.Windows.Forms.GroupBox grpFonts;
        private System.Windows.Forms.GroupBox grpStyles;
        private System.Windows.Forms.RadioButton rdoGungsuh;
        private System.Windows.Forms.RadioButton rdoGulim;
        private System.Windows.Forms.RadioButton rdoDotum;
        private System.Windows.Forms.CheckBox chkItalic;
        private System.Windows.Forms.CheckBox chkUnderline;
        private System.Windows.Forms.CheckBox chkBold;
    }
}

