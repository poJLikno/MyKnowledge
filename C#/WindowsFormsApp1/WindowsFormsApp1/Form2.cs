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
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace WindowsFormsApp1
{
    public partial class Form2 : Form
    {
        private Image _screenshot;
        private Bitmap _screenshotCopy;
        private bool _mouseIsPressed;
        private Graphics _g;
        private Pen _pen;
        private Point _lastMousePos;
        private string _path;

        public Form2(Image screenshot)
        {
            InitializeComponent();
            _screenshot = screenshot;
            _screenshotCopy = new Bitmap(_screenshot);
            pictureBox1.Image = _screenshotCopy;
            comboBox1.SelectedItem = "Red";
            _mouseIsPressed = false;
            _g = Graphics.FromImage(_screenshotCopy);
            _lastMousePos = new Point(0, 0);
            _pen = new Pen(Color.Red, 3.0f)
            {
                StartCap = System.Drawing.Drawing2D.LineCap.Round,
                EndCap = System.Drawing.Drawing2D.LineCap.Round
            };
        }

        private void saveImageToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                if ((_path = saveFileDialog1.FileName) != null)
                {
                    try
                    {
                        EncoderParameters myEncoderParameters = new EncoderParameters(1);
                        EncoderParameter myEncoderParameter = new EncoderParameter(System.Drawing.Imaging.Encoder.Quality, 100L);
                        myEncoderParameters.Param[0] = myEncoderParameter;
                        _screenshotCopy.Save(_path, GetEncoderInfo("image/jpeg"), myEncoderParameters);
                    }
                    catch (Exception) {}
                    Application.Exit();
                }
            }
        }

        private void Form2_FormClosing(object sender, FormClosingEventArgs e)
        {
            Application.Exit();
        }

        private void pictureBox1_MouseDown(object sender, MouseEventArgs e)
        {
            _mouseIsPressed = true;
        }

        private void pictureBox1_MouseUp(object sender, MouseEventArgs e)
        {
            _mouseIsPressed = false;
        }

        private void pictureBox1_MouseMove(object sender, MouseEventArgs e)
        {
            Point p = new Point(e.X * _screenshotCopy.Width / pictureBox1.Width, e.Y * _screenshotCopy.Height / pictureBox1.Height);

            switch (_mouseIsPressed)
            {
                case true:
                    _g.DrawLine(_pen, _lastMousePos, p);
                    pictureBox1.Image = _screenshotCopy;
                    break;

                default:
                    break;
            }

            _lastMousePos = p;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            _g.DrawImage(_screenshot, new Point(0, 0));
            pictureBox1.Image = _screenshotCopy;
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
