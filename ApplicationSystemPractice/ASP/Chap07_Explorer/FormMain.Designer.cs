
namespace Chap07_Explorer
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
            this.pnlPath = new System.Windows.Forms.Panel();
            this.txtPath = new System.Windows.Forms.TextBox();
            this.lblPath = new System.Windows.Forms.Label();
            this.pnlExplorer = new System.Windows.Forms.Panel();
            this.splExplorer = new System.Windows.Forms.Splitter();
            this.lvwFile = new System.Windows.Forms.ListView();
            this.colFilename = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.colFileSize = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.colFileDate = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.cmsListView = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.mnuOpen = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.mnuDetail = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuList = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuSmall = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuLarge = new System.Windows.Forms.ToolStripMenuItem();
            this.imgLst = new System.Windows.Forms.ImageList(this.components);
            this.trvDir = new System.Windows.Forms.TreeView();
            this.pnlPath.SuspendLayout();
            this.pnlExplorer.SuspendLayout();
            this.cmsListView.SuspendLayout();
            this.SuspendLayout();
            // 
            // pnlPath
            // 
            this.pnlPath.Controls.Add(this.txtPath);
            this.pnlPath.Controls.Add(this.lblPath);
            this.pnlPath.Dock = System.Windows.Forms.DockStyle.Top;
            this.pnlPath.Location = new System.Drawing.Point(0, 0);
            this.pnlPath.Name = "pnlPath";
            this.pnlPath.Padding = new System.Windows.Forms.Padding(3);
            this.pnlPath.Size = new System.Drawing.Size(584, 33);
            this.pnlPath.TabIndex = 0;
            // 
            // txtPath
            // 
            this.txtPath.Location = new System.Drawing.Point(65, 6);
            this.txtPath.Name = "txtPath";
            this.txtPath.Size = new System.Drawing.Size(513, 21);
            this.txtPath.TabIndex = 1;
            // 
            // lblPath
            // 
            this.lblPath.AutoSize = true;
            this.lblPath.Location = new System.Drawing.Point(6, 9);
            this.lblPath.Name = "lblPath";
            this.lblPath.Size = new System.Drawing.Size(53, 12);
            this.lblPath.TabIndex = 0;
            this.lblPath.Text = "전체경로";
            // 
            // pnlExplorer
            // 
            this.pnlExplorer.Controls.Add(this.splExplorer);
            this.pnlExplorer.Controls.Add(this.lvwFile);
            this.pnlExplorer.Controls.Add(this.trvDir);
            this.pnlExplorer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pnlExplorer.Location = new System.Drawing.Point(0, 33);
            this.pnlExplorer.Name = "pnlExplorer";
            this.pnlExplorer.Size = new System.Drawing.Size(584, 528);
            this.pnlExplorer.TabIndex = 1;
            // 
            // splExplorer
            // 
            this.splExplorer.Location = new System.Drawing.Point(121, 0);
            this.splExplorer.Name = "splExplorer";
            this.splExplorer.Size = new System.Drawing.Size(3, 528);
            this.splExplorer.TabIndex = 2;
            this.splExplorer.TabStop = false;
            // 
            // lvwFile
            // 
            this.lvwFile.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.colFilename,
            this.colFileSize,
            this.colFileDate});
            this.lvwFile.ContextMenuStrip = this.cmsListView;
            this.lvwFile.Dock = System.Windows.Forms.DockStyle.Fill;
            this.lvwFile.HideSelection = false;
            this.lvwFile.LargeImageList = this.imgLst;
            this.lvwFile.Location = new System.Drawing.Point(121, 0);
            this.lvwFile.Name = "lvwFile";
            this.lvwFile.Size = new System.Drawing.Size(463, 528);
            this.lvwFile.SmallImageList = this.imgLst;
            this.lvwFile.TabIndex = 1;
            this.lvwFile.UseCompatibleStateImageBehavior = false;
            this.lvwFile.DoubleClick += new System.EventHandler(this.lvwFile_DoubleClick);
            // 
            // colFilename
            // 
            this.colFilename.Text = "이름";
            // 
            // colFileSize
            // 
            this.colFileSize.Text = "크기";
            // 
            // colFileDate
            // 
            this.colFileDate.Text = "수정한 날짜";
            // 
            // cmsListView
            // 
            this.cmsListView.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnuOpen,
            this.toolStripSeparator1,
            this.mnuDetail,
            this.mnuList,
            this.mnuSmall,
            this.mnuLarge});
            this.cmsListView.Name = "cmsListView";
            this.cmsListView.Size = new System.Drawing.Size(181, 142);
            // 
            // mnuOpen
            // 
            this.mnuOpen.Name = "mnuOpen";
            this.mnuOpen.Size = new System.Drawing.Size(180, 22);
            this.mnuOpen.Text = "열기";
            this.mnuOpen.Click += new System.EventHandler(this.mnuOpen_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(177, 6);
            // 
            // mnuDetail
            // 
            this.mnuDetail.Name = "mnuDetail";
            this.mnuDetail.Size = new System.Drawing.Size(180, 22);
            this.mnuDetail.Text = "자세히";
            this.mnuDetail.Click += new System.EventHandler(this.mnu_Click);
            // 
            // mnuList
            // 
            this.mnuList.Name = "mnuList";
            this.mnuList.Size = new System.Drawing.Size(180, 22);
            this.mnuList.Text = "간단히";
            this.mnuList.Click += new System.EventHandler(this.mnu_Click);
            // 
            // mnuSmall
            // 
            this.mnuSmall.Name = "mnuSmall";
            this.mnuSmall.Size = new System.Drawing.Size(180, 22);
            this.mnuSmall.Text = "작은 아이콘";
            this.mnuSmall.Click += new System.EventHandler(this.mnu_Click);
            // 
            // mnuLarge
            // 
            this.mnuLarge.Name = "mnuLarge";
            this.mnuLarge.Size = new System.Drawing.Size(180, 22);
            this.mnuLarge.Text = "큰 아이콘";
            this.mnuLarge.Click += new System.EventHandler(this.mnu_Click);
            // 
            // imgLst
            // 
            this.imgLst.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imgLst.ImageStream")));
            this.imgLst.TransparentColor = System.Drawing.Color.Transparent;
            this.imgLst.Images.SetKeyName(0, "android.jpg");
            this.imgLst.Images.SetKeyName(1, "apple.png");
            this.imgLst.Images.SetKeyName(2, "steam.png");
            this.imgLst.Images.SetKeyName(3, "window.png");
            // 
            // trvDir
            // 
            this.trvDir.Dock = System.Windows.Forms.DockStyle.Left;
            this.trvDir.ImageIndex = 0;
            this.trvDir.ImageList = this.imgLst;
            this.trvDir.Location = new System.Drawing.Point(0, 0);
            this.trvDir.Name = "trvDir";
            this.trvDir.SelectedImageIndex = 0;
            this.trvDir.Size = new System.Drawing.Size(121, 528);
            this.trvDir.TabIndex = 0;
            this.trvDir.BeforeExpand += new System.Windows.Forms.TreeViewCancelEventHandler(this.trvDir_BeforeExpand);
            this.trvDir.BeforeSelect += new System.Windows.Forms.TreeViewCancelEventHandler(this.trvDir_BeforeSelect);
            // 
            // FormMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(584, 561);
            this.Controls.Add(this.pnlExplorer);
            this.Controls.Add(this.pnlPath);
            this.Name = "FormMain";
            this.Text = "Explorer";
            this.Load += new System.EventHandler(this.FormMain_Load);
            this.pnlPath.ResumeLayout(false);
            this.pnlPath.PerformLayout();
            this.pnlExplorer.ResumeLayout(false);
            this.cmsListView.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel pnlPath;
        private System.Windows.Forms.TextBox txtPath;
        private System.Windows.Forms.Label lblPath;
        private System.Windows.Forms.Panel pnlExplorer;
        private System.Windows.Forms.Splitter splExplorer;
        private System.Windows.Forms.ListView lvwFile;
        private System.Windows.Forms.ColumnHeader colFilename;
        private System.Windows.Forms.ColumnHeader colFileSize;
        private System.Windows.Forms.ColumnHeader colFileDate;
        private System.Windows.Forms.TreeView trvDir;
        private System.Windows.Forms.ContextMenuStrip cmsListView;
        private System.Windows.Forms.ToolStripMenuItem mnuOpen;
        private System.Windows.Forms.ToolStripMenuItem mnuDetail;
        private System.Windows.Forms.ToolStripMenuItem mnuList;
        private System.Windows.Forms.ToolStripMenuItem mnuSmall;
        private System.Windows.Forms.ToolStripMenuItem mnuLarge;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ImageList imgLst;
    }
}

