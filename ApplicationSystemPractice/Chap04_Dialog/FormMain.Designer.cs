
namespace Chap04_Dialog
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
            this.lblApple = new System.Windows.Forms.Label();
            this.txtApple = new System.Windows.Forms.TextBox();
            this.lblbanana = new System.Windows.Forms.Label();
            this.txtBanana = new System.Windows.Forms.TextBox();
            this.btnSubmit = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // lblApple
            // 
            this.lblApple.AutoSize = true;
            this.lblApple.Location = new System.Drawing.Point(12, 15);
            this.lblApple.Name = "lblApple";
            this.lblApple.Size = new System.Drawing.Size(60, 12);
            this.lblApple.TabIndex = 0;
            this.lblApple.Text = "# of apple";
            // 
            // txtApple
            // 
            this.txtApple.Location = new System.Drawing.Point(89, 12);
            this.txtApple.Name = "txtApple";
            this.txtApple.Size = new System.Drawing.Size(100, 21);
            this.txtApple.TabIndex = 1;
            this.txtApple.TextChanged += new System.EventHandler(this.txt_TextChanged);
            // 
            // lblbanana
            // 
            this.lblbanana.AutoSize = true;
            this.lblbanana.Location = new System.Drawing.Point(12, 42);
            this.lblbanana.Name = "lblbanana";
            this.lblbanana.Size = new System.Drawing.Size(71, 12);
            this.lblbanana.TabIndex = 0;
            this.lblbanana.Text = "# of banana";
            // 
            // txtBanana
            // 
            this.txtBanana.Location = new System.Drawing.Point(89, 39);
            this.txtBanana.Name = "txtBanana";
            this.txtBanana.Size = new System.Drawing.Size(100, 21);
            this.txtBanana.TabIndex = 1;
            this.txtBanana.TextChanged += new System.EventHandler(this.txt_TextChanged);
            // 
            // btnSubmit
            // 
            this.btnSubmit.Location = new System.Drawing.Point(89, 66);
            this.btnSubmit.Name = "btnSubmit";
            this.btnSubmit.Size = new System.Drawing.Size(100, 23);
            this.btnSubmit.TabIndex = 2;
            this.btnSubmit.Text = "&Submit";
            this.btnSubmit.UseVisualStyleBackColor = true;
            this.btnSubmit.Click += new System.EventHandler(this.btnSubmit_Click);
            // 
            // FormMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(201, 101);
            this.Controls.Add(this.btnSubmit);
            this.Controls.Add(this.txtBanana);
            this.Controls.Add(this.lblbanana);
            this.Controls.Add(this.txtApple);
            this.Controls.Add(this.lblApple);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "FormMain";
            this.Text = "Dialog";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label lblApple;
        private System.Windows.Forms.TextBox txtApple;
        private System.Windows.Forms.Label lblbanana;
        private System.Windows.Forms.TextBox txtBanana;
        private System.Windows.Forms.Button btnSubmit;
    }
}

