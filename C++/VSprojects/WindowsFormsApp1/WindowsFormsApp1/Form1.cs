using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Imaging;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows.Input;
using Encoder = System.Drawing.Imaging.Encoder;

namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        private Image _screenshot;
        private string _path;
        //private string _filename;

        public Form1()
        {
            InitializeComponent();
            if (Clipboard.ContainsImage())
            {
                _screenshot = Clipboard.GetImage();
                string date = DateTime.Now.ToString();
                _path = "C:\\Users\\" + Environment.UserName + "\\Pictures\\" + "Screenshot_" + date.Replace(':', '.').Replace(' ', '_') + ".jpg";
                //_filename = "Screenshot_" + date.Replace(':', '.').Replace(' ', '_') + ".jpg";

                pictureBox1.Image = _screenshot;
                textBox1.Text = _path;// + "\\" + _filename;
            }
            else Application.Exit();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                string str = textBox1.Text;

                EncoderParameters myEncoderParameters = new EncoderParameters(1);
                EncoderParameter myEncoderParameter = new EncoderParameter(Encoder.Quality, trackBar1.Value);
                myEncoderParameters.Param[0] = myEncoderParameter;
                _screenshot.Save(str, GetEncoderInfo("image/jpeg"), myEncoderParameters);
            } catch (Exception) {}
            Application.Exit();
        }

        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            toolTip1.SetToolTip(trackBar1, trackBar1.Value.ToString() + "%");
        }

        private void button2_Click(object sender, EventArgs e)
        {
            /*if (folderBrowserDialog1.ShowDialog() == DialogResult.OK)
            {
                textBox1.Text = folderBrowserDialog1.SelectedPath + "\\" + _filename;
            }*/
            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                if ((_path = saveFileDialog1.FileName) != null)
                {
                    textBox1.Text = _path;
                }
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            this.Hide();
            Form2 form2 = new Form2(_screenshot);
            form2.Show();
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            Application.Exit();
        }

        private ImageCodecInfo GetEncoderInfo(String mimeType)
        {
            int j;
            ImageCodecInfo[] encoders;
            encoders = ImageCodecInfo.GetImageEncoders();
            for (j = 0; j < encoders.Length; ++j)
            {
                if (encoders[j].MimeType == mimeType)
                    return encoders[j];
            }
            return null;
        }
    }
}