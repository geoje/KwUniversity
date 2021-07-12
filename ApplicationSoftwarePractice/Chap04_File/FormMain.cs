using System;
using System.Collections.Generic;
using System.IO;
using System.Windows.Forms;

namespace Chap04_File
{
    public partial class FormMain : Form
    {
        List<string[]> awsList = new List<string[]>();

        public FormMain()
        {
            InitializeComponent();

            ofd.Filter = "CSV (*.csv)|*.csv|" + "All files (*.*)|*.*";
            dtpDate.Value = DateTime.ParseExact(
                DateTime.Now.ToString("yyyy-MM") + "-01",
                "yyyy-MM-dd",
                null);
            dtpTime.Value = DateTime.ParseExact("00:00:00", "HH:mm:ss", null);
        }

        private void tmiOpen_Click(object sender, EventArgs e)
        {
            if (ofd.ShowDialog() != DialogResult.OK) return;

            StreamReader sr = new StreamReader(ofd.FileName);
            awsList.Clear();

            try
            {
                Text = Path.GetFileName(ofd.FileName);

                string line;
                while ((line = sr.ReadLine()) != null)
                    awsList.Add(line.Split(','));
            }
            catch (Exception ex)
            {
                MessageBox.Show(
                    ex.Message,
                    "File Open Error",
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Error);
            }
            finally
            {
                sr.Close();
            }
        }
        private DateTime GetDate()
        {
            string date = dtpDate.Value.ToString("yyyy-MM-dd");
            string time = dtpTime.Value.ToString("HH:mm");

            return DateTime.ParseExact(date + ' ' + time, "yyyy-MM-dd HH:mm", null);
        }
        private string GetTemperature()
        {
            string curDateString = GetDate().ToString("yyyy-MM-dd HH:mm");

            for (int i = 0; i < awsList.Count; i++)
                if (awsList[i][1] == curDateString)
                    return awsList[i][2];
            return "";
        }
        private void btnQuery_Click(object sender, EventArgs e)
        {
            if (ofd.FileName == "")
            {
                MessageBox.Show("입력된 파일이 없습니다.");
                return;
            }

            string TemperatureString = GetTemperature();
            if (string.IsNullOrEmpty(TemperatureString))
                MessageBox.Show($"{GetDate()}에는 자료가 없습니다.");
            else
                MessageBox.Show($"{GetDate()}에는 {TemperatureString}도 입니다.");
        }
        private void btnSave_Click(object sender, EventArgs e)
        {
            if (ofd.FileName == "")
            {
                MessageBox.Show("입력된 파일이 없습니다.");
                return;
            }

            StreamWriter sw = new StreamWriter(ofd.FileName, true);
            sw.WriteLine(GetDate().ToString("yyyy-MM-dd HH:mm," + GetTemperature()));
            sw.Close();
        }
        private void btnExit_Click(object sender, EventArgs e)
            => Close();
    }
}
