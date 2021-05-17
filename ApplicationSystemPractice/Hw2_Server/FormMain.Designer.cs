
namespace Hw2_Server
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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FormMain));
            this.ilstTool = new System.Windows.Forms.ImageList(this.components);
            this.tbrTool = new System.Windows.Forms.ToolBar();
            this.tbtnNew = new System.Windows.Forms.ToolBarButton();
            this.tbtnLine = new System.Windows.Forms.ToolBarButton();
            this.tbtnRect = new System.Windows.Forms.ToolBarButton();
            this.tbtnCircle = new System.Windows.Forms.ToolBarButton();
            this.tbtnLine0 = new System.Windows.Forms.ToolBarButton();
            this.tbtnLine1 = new System.Windows.Forms.ToolBarButton();
            this.tbtnLine2 = new System.Windows.Forms.ToolBarButton();
            this.tbtnLine3 = new System.Windows.Forms.ToolBarButton();
            this.pnlNetwork = new System.Windows.Forms.Panel();
            this.btnSend = new System.Windows.Forms.Button();
            this.lblWord = new System.Windows.Forms.Label();
            this.txtWord = new System.Windows.Forms.TextBox();
            this.txtId = new System.Windows.Forms.TextBox();
            this.lblId = new System.Windows.Forms.Label();
            this.pnlPaint = new System.Windows.Forms.Panel();
            this.pnlNetwork.SuspendLayout();
            this.SuspendLayout();
            // 
            // ilstTool
            // 
            this.ilstTool.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("ilstTool.ImageStream")));
            this.ilstTool.TransparentColor = System.Drawing.Color.Transparent;
            this.ilstTool.Images.SetKeyName(0, "new_image.png");
            this.ilstTool.Images.SetKeyName(1, "line_image.png");
            this.ilstTool.Images.SetKeyName(2, "rect_image.png");
            this.ilstTool.Images.SetKeyName(3, "circle_image.png");
            this.ilstTool.Images.SetKeyName(4, "line0_image.png");
            this.ilstTool.Images.SetKeyName(5, "line1_image.png");
            this.ilstTool.Images.SetKeyName(6, "line2_image.png");
            this.ilstTool.Images.SetKeyName(7, "line3_image.png");
            // 
            // tbrTool
            // 
            this.tbrTool.Buttons.AddRange(new System.Windows.Forms.ToolBarButton[] {
            this.tbtnNew,
            this.tbtnLine,
            this.tbtnRect,
            this.tbtnCircle,
            this.tbtnLine0,
            this.tbtnLine1,
            this.tbtnLine2,
            this.tbtnLine3});
            this.tbrTool.DropDownArrows = true;
            this.tbrTool.Enabled = false;
            this.tbrTool.ImageList = this.ilstTool;
            this.tbrTool.Location = new System.Drawing.Point(0, 0);
            this.tbrTool.Name = "tbrTool";
            this.tbrTool.ShowToolTips = true;
            this.tbrTool.Size = new System.Drawing.Size(584, 48);
            this.tbrTool.TabIndex = 1;
            this.tbrTool.ButtonClick += new System.Windows.Forms.ToolBarButtonClickEventHandler(this.tbrTool_ButtonClick);
            // 
            // tbtnNew
            // 
            this.tbtnNew.ImageIndex = 0;
            this.tbtnNew.Name = "tbtnNew";
            // 
            // tbtnLine
            // 
            this.tbtnLine.ImageIndex = 1;
            this.tbtnLine.Name = "tbtnLine";
            this.tbtnLine.Pushed = true;
            // 
            // tbtnRect
            // 
            this.tbtnRect.ImageIndex = 2;
            this.tbtnRect.Name = "tbtnRect";
            // 
            // tbtnCircle
            // 
            this.tbtnCircle.ImageIndex = 3;
            this.tbtnCircle.Name = "tbtnCircle";
            // 
            // tbtnLine0
            // 
            this.tbtnLine0.ImageIndex = 4;
            this.tbtnLine0.Name = "tbtnLine0";
            // 
            // tbtnLine1
            // 
            this.tbtnLine1.ImageIndex = 5;
            this.tbtnLine1.Name = "tbtnLine1";
            this.tbtnLine1.Pushed = true;
            // 
            // tbtnLine2
            // 
            this.tbtnLine2.ImageIndex = 6;
            this.tbtnLine2.Name = "tbtnLine2";
            // 
            // tbtnLine3
            // 
            this.tbtnLine3.ImageIndex = 7;
            this.tbtnLine3.Name = "tbtnLine3";
            // 
            // pnlNetwork
            // 
            this.pnlNetwork.BackColor = System.Drawing.SystemColors.GradientActiveCaption;
            this.pnlNetwork.Controls.Add(this.btnSend);
            this.pnlNetwork.Controls.Add(this.lblWord);
            this.pnlNetwork.Controls.Add(this.txtWord);
            this.pnlNetwork.Controls.Add(this.txtId);
            this.pnlNetwork.Controls.Add(this.lblId);
            this.pnlNetwork.Dock = System.Windows.Forms.DockStyle.Top;
            this.pnlNetwork.Location = new System.Drawing.Point(0, 48);
            this.pnlNetwork.Margin = new System.Windows.Forms.Padding(0);
            this.pnlNetwork.Name = "pnlNetwork";
            this.pnlNetwork.Size = new System.Drawing.Size(584, 32);
            this.pnlNetwork.TabIndex = 2;
            // 
            // btnSend
            // 
            this.btnSend.Enabled = false;
            this.btnSend.Location = new System.Drawing.Point(450, 4);
            this.btnSend.Name = "btnSend";
            this.btnSend.Size = new System.Drawing.Size(75, 23);
            this.btnSend.TabIndex = 3;
            this.btnSend.Text = "전송";
            this.btnSend.UseVisualStyleBackColor = true;
            this.btnSend.Click += new System.EventHandler(this.btnSend_Click);
            // 
            // lblWord
            // 
            this.lblWord.AutoSize = true;
            this.lblWord.Location = new System.Drawing.Point(238, 9);
            this.lblWord.Name = "lblWord";
            this.lblWord.Size = new System.Drawing.Size(41, 12);
            this.lblWord.TabIndex = 2;
            this.lblWord.Text = "제시어";
            // 
            // txtWord
            // 
            this.txtWord.Location = new System.Drawing.Point(285, 6);
            this.txtWord.Name = "txtWord";
            this.txtWord.ReadOnly = true;
            this.txtWord.Size = new System.Drawing.Size(100, 21);
            this.txtWord.TabIndex = 1;
            // 
            // txtId
            // 
            this.txtId.Location = new System.Drawing.Point(89, 6);
            this.txtId.Name = "txtId";
            this.txtId.ReadOnly = true;
            this.txtId.Size = new System.Drawing.Size(100, 21);
            this.txtId.TabIndex = 1;
            // 
            // lblId
            // 
            this.lblId.AutoSize = true;
            this.lblId.Location = new System.Drawing.Point(39, 9);
            this.lblId.Name = "lblId";
            this.lblId.Size = new System.Drawing.Size(44, 12);
            this.lblId.TabIndex = 0;
            this.lblId.Text = "접속 ID";
            // 
            // pnlPaint
            // 
            this.pnlPaint.BackColor = System.Drawing.SystemColors.Window;
            this.pnlPaint.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pnlPaint.Enabled = false;
            this.pnlPaint.Location = new System.Drawing.Point(0, 80);
            this.pnlPaint.Margin = new System.Windows.Forms.Padding(0);
            this.pnlPaint.Name = "pnlPaint";
            this.pnlPaint.Size = new System.Drawing.Size(584, 361);
            this.pnlPaint.TabIndex = 3;
            this.pnlPaint.Paint += new System.Windows.Forms.PaintEventHandler(this.pnlPaint_Paint);
            this.pnlPaint.MouseDown += new System.Windows.Forms.MouseEventHandler(this.pnlPaint_MouseDown);
            this.pnlPaint.MouseMove += new System.Windows.Forms.MouseEventHandler(this.pnlPaint_MouseMove);
            // 
            // FormMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(584, 441);
            this.Controls.Add(this.pnlPaint);
            this.Controls.Add(this.pnlNetwork);
            this.Controls.Add(this.tbrTool);
            this.Name = "FormMain";
            this.Text = "CatchMindServer";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.FormMain_FormClosing);
            this.Shown += new System.EventHandler(this.FormMain_Shown);
            this.pnlNetwork.ResumeLayout(false);
            this.pnlNetwork.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.ImageList ilstTool;
        private System.Windows.Forms.ToolBar tbrTool;
        private System.Windows.Forms.ToolBarButton tbtnNew;
        private System.Windows.Forms.ToolBarButton tbtnLine;
        private System.Windows.Forms.ToolBarButton tbtnRect;
        private System.Windows.Forms.ToolBarButton tbtnCircle;
        private System.Windows.Forms.ToolBarButton tbtnLine0;
        private System.Windows.Forms.ToolBarButton tbtnLine1;
        private System.Windows.Forms.ToolBarButton tbtnLine2;
        private System.Windows.Forms.ToolBarButton tbtnLine3;
        private System.Windows.Forms.Panel pnlNetwork;
        private System.Windows.Forms.Label lblWord;
        private System.Windows.Forms.TextBox txtWord;
        private System.Windows.Forms.TextBox txtId;
        private System.Windows.Forms.Label lblId;
        private System.Windows.Forms.Panel pnlPaint;
        private System.Windows.Forms.Button btnSend;
    }
}

