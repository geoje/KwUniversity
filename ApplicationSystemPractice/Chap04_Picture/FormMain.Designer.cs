
namespace Chap04_Picture
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
            this.picProfile = new System.Windows.Forms.PictureBox();
            this.grpProfile = new System.Windows.Forms.GroupBox();
            this.grpChange = new System.Windows.Forms.GroupBox();
            this.grpOption = new System.Windows.Forms.GroupBox();
            this.rdoNormal = new System.Windows.Forms.RadioButton();
            this.rdoStretchImage = new System.Windows.Forms.RadioButton();
            this.rdoAutoSize = new System.Windows.Forms.RadioButton();
            this.rdoCenterImage = new System.Windows.Forms.RadioButton();
            this.rdoZoom = new System.Windows.Forms.RadioButton();
            this.chkVisible = new System.Windows.Forms.CheckBox();
            this.lblUrl = new System.Windows.Forms.Label();
            this.txtUrl = new System.Windows.Forms.TextBox();
            this.btnChange = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.picProfile)).BeginInit();
            this.grpProfile.SuspendLayout();
            this.grpChange.SuspendLayout();
            this.grpOption.SuspendLayout();
            this.SuspendLayout();
            // 
            // picProfile
            // 
            this.picProfile.Location = new System.Drawing.Point(12, 12);
            this.picProfile.Name = "picProfile";
            this.picProfile.Size = new System.Drawing.Size(200, 200);
            this.picProfile.TabIndex = 0;
            this.picProfile.TabStop = false;
            // 
            // grpProfile
            // 
            this.grpProfile.Controls.Add(this.grpOption);
            this.grpProfile.Controls.Add(this.grpChange);
            this.grpProfile.Location = new System.Drawing.Point(218, 12);
            this.grpProfile.Name = "grpProfile";
            this.grpProfile.Size = new System.Drawing.Size(433, 200);
            this.grpProfile.TabIndex = 1;
            this.grpProfile.TabStop = false;
            this.grpProfile.Text = "프로필 관리";
            // 
            // grpChange
            // 
            this.grpChange.Controls.Add(this.btnChange);
            this.grpChange.Controls.Add(this.txtUrl);
            this.grpChange.Controls.Add(this.lblUrl);
            this.grpChange.Location = new System.Drawing.Point(6, 20);
            this.grpChange.Name = "grpChange";
            this.grpChange.Size = new System.Drawing.Size(421, 104);
            this.grpChange.TabIndex = 0;
            this.grpChange.TabStop = false;
            this.grpChange.Text = "사진변경";
            // 
            // grpOption
            // 
            this.grpOption.Controls.Add(this.chkVisible);
            this.grpOption.Controls.Add(this.rdoZoom);
            this.grpOption.Controls.Add(this.rdoCenterImage);
            this.grpOption.Controls.Add(this.rdoAutoSize);
            this.grpOption.Controls.Add(this.rdoStretchImage);
            this.grpOption.Controls.Add(this.rdoNormal);
            this.grpOption.Location = new System.Drawing.Point(6, 130);
            this.grpOption.Name = "grpOption";
            this.grpOption.Size = new System.Drawing.Size(421, 64);
            this.grpOption.TabIndex = 0;
            this.grpOption.TabStop = false;
            this.grpOption.Text = "옵션";
            // 
            // rdoNormal
            // 
            this.rdoNormal.AutoSize = true;
            this.rdoNormal.Location = new System.Drawing.Point(6, 20);
            this.rdoNormal.Name = "rdoNormal";
            this.rdoNormal.Size = new System.Drawing.Size(64, 16);
            this.rdoNormal.TabIndex = 0;
            this.rdoNormal.TabStop = true;
            this.rdoNormal.Text = "Normal";
            this.rdoNormal.UseVisualStyleBackColor = true;
            this.rdoNormal.CheckedChanged += new System.EventHandler(this.rdo_CheckedChanged);
            // 
            // rdoStretchImage
            // 
            this.rdoStretchImage.AutoSize = true;
            this.rdoStretchImage.Location = new System.Drawing.Point(76, 20);
            this.rdoStretchImage.Name = "rdoStretchImage";
            this.rdoStretchImage.Size = new System.Drawing.Size(97, 16);
            this.rdoStretchImage.TabIndex = 0;
            this.rdoStretchImage.TabStop = true;
            this.rdoStretchImage.Text = "StretchImage";
            this.rdoStretchImage.UseVisualStyleBackColor = true;
            this.rdoStretchImage.CheckedChanged += new System.EventHandler(this.rdo_CheckedChanged);
            // 
            // rdoAutoSize
            // 
            this.rdoAutoSize.AutoSize = true;
            this.rdoAutoSize.Location = new System.Drawing.Point(179, 20);
            this.rdoAutoSize.Name = "rdoAutoSize";
            this.rdoAutoSize.Size = new System.Drawing.Size(73, 16);
            this.rdoAutoSize.TabIndex = 0;
            this.rdoAutoSize.TabStop = true;
            this.rdoAutoSize.Text = "AutoSize";
            this.rdoAutoSize.UseVisualStyleBackColor = true;
            this.rdoAutoSize.CheckedChanged += new System.EventHandler(this.rdo_CheckedChanged);
            // 
            // rdoCenterImage
            // 
            this.rdoCenterImage.AutoSize = true;
            this.rdoCenterImage.Location = new System.Drawing.Point(258, 20);
            this.rdoCenterImage.Name = "rdoCenterImage";
            this.rdoCenterImage.Size = new System.Drawing.Size(95, 16);
            this.rdoCenterImage.TabIndex = 0;
            this.rdoCenterImage.TabStop = true;
            this.rdoCenterImage.Text = "CenterImage";
            this.rdoCenterImage.UseVisualStyleBackColor = true;
            this.rdoCenterImage.CheckedChanged += new System.EventHandler(this.rdo_CheckedChanged);
            // 
            // rdoZoom
            // 
            this.rdoZoom.AutoSize = true;
            this.rdoZoom.Location = new System.Drawing.Point(359, 20);
            this.rdoZoom.Name = "rdoZoom";
            this.rdoZoom.Size = new System.Drawing.Size(56, 16);
            this.rdoZoom.TabIndex = 0;
            this.rdoZoom.TabStop = true;
            this.rdoZoom.Text = "Zoom";
            this.rdoZoom.UseVisualStyleBackColor = true;
            this.rdoZoom.CheckedChanged += new System.EventHandler(this.rdo_CheckedChanged);
            // 
            // chkVisible
            // 
            this.chkVisible.AutoSize = true;
            this.chkVisible.Location = new System.Drawing.Point(6, 42);
            this.chkVisible.Name = "chkVisible";
            this.chkVisible.Size = new System.Drawing.Size(60, 16);
            this.chkVisible.TabIndex = 1;
            this.chkVisible.Text = "숨기기";
            this.chkVisible.UseVisualStyleBackColor = true;
            this.chkVisible.CheckedChanged += new System.EventHandler(this.chkVisible_CheckedChanged);
            // 
            // lblUrl
            // 
            this.lblUrl.AutoSize = true;
            this.lblUrl.Location = new System.Drawing.Point(6, 23);
            this.lblUrl.Name = "lblUrl";
            this.lblUrl.Size = new System.Drawing.Size(20, 12);
            this.lblUrl.TabIndex = 0;
            this.lblUrl.Text = "Url";
            // 
            // txtUrl
            // 
            this.txtUrl.Location = new System.Drawing.Point(32, 20);
            this.txtUrl.Multiline = true;
            this.txtUrl.Name = "txtUrl";
            this.txtUrl.Size = new System.Drawing.Size(380, 49);
            this.txtUrl.TabIndex = 1;
            // 
            // btnChange
            // 
            this.btnChange.Location = new System.Drawing.Point(337, 75);
            this.btnChange.Name = "btnChange";
            this.btnChange.Size = new System.Drawing.Size(75, 23);
            this.btnChange.TabIndex = 2;
            this.btnChange.Text = "Change";
            this.btnChange.UseVisualStyleBackColor = true;
            this.btnChange.Click += new System.EventHandler(this.btnChange_Click);
            // 
            // FormMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(663, 224);
            this.Controls.Add(this.grpProfile);
            this.Controls.Add(this.picProfile);
            this.Name = "FormMain";
            this.Text = "PictureBox";
            ((System.ComponentModel.ISupportInitialize)(this.picProfile)).EndInit();
            this.grpProfile.ResumeLayout(false);
            this.grpChange.ResumeLayout(false);
            this.grpChange.PerformLayout();
            this.grpOption.ResumeLayout(false);
            this.grpOption.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.PictureBox picProfile;
        private System.Windows.Forms.GroupBox grpProfile;
        private System.Windows.Forms.GroupBox grpOption;
        private System.Windows.Forms.CheckBox chkVisible;
        private System.Windows.Forms.RadioButton rdoZoom;
        private System.Windows.Forms.RadioButton rdoCenterImage;
        private System.Windows.Forms.RadioButton rdoAutoSize;
        private System.Windows.Forms.RadioButton rdoStretchImage;
        private System.Windows.Forms.RadioButton rdoNormal;
        private System.Windows.Forms.GroupBox grpChange;
        private System.Windows.Forms.Button btnChange;
        private System.Windows.Forms.TextBox txtUrl;
        private System.Windows.Forms.Label lblUrl;
    }
}

