using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        int i, x, y, gx, gy, dx, dy,sut,golman=0,igrac=0;
        bool g,vg;

        public Form1()
        {
            InitializeComponent();
        }

        private void golmanspreman_MouseUp(object sender, MouseEventArgs e)
        {
            x = 161 + 15;
            y = 468 + 15;
            gx = e.X - 15+599;
            gy = e.Y - 15+267;
            dx = (gx - x) / 3;
            dy = (gy - y) / 3;
            timer2.Enabled = true;
            timer1.Enabled = false;
        }

        private void Form1_Load(object sender, EventArgs e)
        {                                                                          
            golmansredina.Visible = false;
            golmandoleD.Visible = false;
            golmandoleL.Visible = false;
            golmangoreD.Visible = false;
            golmangoreL.Visible = false;
            golmanodbrana.Visible = false;
            golmanprimio.Visible = false;
            igracsutira.Visible = false;
            lopta.SizeMode = PictureBoxSizeMode.StretchImage;
            pogodak.Visible = false;
            promasaj.Visible = false;
            button1.Visible = false;
            label3.Text = Convert.ToString(golman);
            label4.Text = Convert.ToString(igrac);
            pictureBox1.Visible = false;
            pictureBox2.Visible = false;
        }
        private void timer1_Tick(object sender, EventArgs e)
            {
            pictureBox1.Visible = false;
            pictureBox2.Visible = false;
            pogodak.Visible = false;
            promasaj.Visible = false;
            lopta.Visible = true;
            lopta.Location = new Point(161, 468);
            lopta.Size = new System.Drawing.Size(70, 70);
            lopta.SizeMode = PictureBoxSizeMode.StretchImage;
            golmanprimio.Visible = false;
            golmanodbrana.Visible = false;
            golmanspreman.Visible = true;
            button1.Visible = false;


        }
        private void Form1_MouseUp(object sender, MouseEventArgs e)
        {                                                               
            x = 161+15;
            y = 468+15;
            gx = e.X-15;
            gy = e.Y-15;
            dx = (gx - x) / 3;
            dy = (gy - y) / 3;
            timer2.Enabled = true;
            timer1.Enabled = false;

        }
        private void timer2_Tick(object sender, EventArgs e)
        {
            Random r = new Random();
            lopta.Location = new Point(x, y);
            lopta.Size = new System.Drawing.Size(lopta.Width - 7, lopta.Height - 7);
            lopta.SizeMode = PictureBoxSizeMode.StretchImage;
            x += dx;
            y += dy;
            if(sut!=1)if (x > (gx-2*dx)) switch (r.Next(4))
                {
                    case 0: golmansredina.Visible = true; golmanspreman.Visible = false; i = 0; sut = 1; break;      
                    case 1:
                            if (gx < 657)
                            {
                                golmandoleL.Visible = true; golmanspreman.Visible = false; i = 1; sut = 1; break;
                            }
                            else
                            {
                                golmandoleD.Visible = true; golmanspreman.Visible = false; i = 1; sut = 1; break;
                            }
                        case 2: if (gx < 657)
                            {
                                golmangoreL.Visible = true; golmanspreman.Visible = false; i = 2; sut = 1; break;
                            }
                            else
                            {
                                golmangoreD.Visible = true; golmanspreman.Visible = false; i = 2; sut = 1; break;
                            }
                    }
            igracstoji.Visible = false;
            igracsutira.Visible = true;
            if (x > gx || y < gy)
            {
                if (gx < 395 || gx > 885 || gy > 380 || gy < 195) vg = true;
                else vg = false;
                    timer2.Enabled = false;
                timer4.Enabled = true;
            }

        }

        private void timer3_Tick(object sender, EventArgs e)
        {
            
            switch (i)
            {
                case 0: golmansredina.Visible = false;
                    if (vg)
                    {
                        golmanodbrana.Visible = true;
                        lopta.Visible = false;
                        promasaj.Visible = true;
                    }
                    else if (!g)                                               
                    {
                        golmanprimio.Visible = true;
                        lopta.Visible = false;
                        pogodak.Visible = true;
                    }
                    else                                                           
                    {
                        golmanodbrana.Visible = true;
                        lopta.Visible = false;
                        promasaj.Visible = true;
                    }
                    igracsutira.Visible = false;
                    igracstoji.Visible = true;
                    break;
                case 1:
                    if (gx < 657) golmandoleL.Visible = false;
                    else golmandoleD.Visible = false;
                    if (vg)
                    {
                        golmanodbrana.Visible = true;
                        lopta.Visible = false;
                        promasaj.Visible = true;
                    }
                    else if(!g)
                    {
                        golmanprimio.Visible = true;
                        lopta.Visible = false;
                        pogodak.Visible = true;
                    }
                    else
                    {
                        golmanodbrana.Visible = true;
                        lopta.Visible = false;
                        promasaj.Visible = true;
                    }
                    igracsutira.Visible = false;
                    igracstoji.Visible = true;
                    break;
                case 2: if (gx < 657) golmangoreL.Visible = false;
                    else golmangoreD.Visible = false;
                    if (vg)
                    {
                        golmanodbrana.Visible = true;
                        lopta.Visible = false;
                        promasaj.Visible = true;
                    }
                    else if(!g)
                    {
                        golmanprimio.Visible = true;
                        lopta.Visible = false;
                        pogodak.Visible = true;
                    }
                    else
                    {
                        golmanodbrana.Visible = true;
                        lopta.Visible = false;
                        promasaj.Visible = true;
                    }
                    igracsutira.Visible = false;
                    igracstoji.Visible = true;
                    break;
            }
            button1.Visible = true;                                                             

        }

        private void timer4_Tick(object sender, EventArgs e)
        {
            pictureBox1.Visible = true;
            pictureBox2.Visible = true;
            switch (i)
            {
                case 0: g = lopta.Bounds.IntersectsWith(golmansredina.Bounds); break;
                case 1:
                    if (gx < 657) g = lopta.Bounds.IntersectsWith(golmandoleL.Bounds);
                    else g = lopta.Bounds.IntersectsWith(golmandoleD.Bounds);
                    break;
                case 2:
                    if (gx < 657) g = lopta.Bounds.IntersectsWith(golmangoreL.Bounds);
                    else g = lopta.Bounds.IntersectsWith(golmangoreD.Bounds);
                    break;
            }
            if (i == 2)
            {   
                if(gx<657 && g && (lopta.Bounds.IntersectsWith(pictureBox1.Bounds) || lopta.Bounds.IntersectsWith(pictureBox3.Bounds) || lopta.Bounds.IntersectsWith(pictureBox5.Bounds))) g = false;
                else if (g && (lopta.Bounds.IntersectsWith(pictureBox2.Bounds) || lopta.Bounds.IntersectsWith(pictureBox3.Bounds) || lopta.Bounds.IntersectsWith(pictureBox6.Bounds))) g = false;
            }
            if (i == 1) if (gy < 315) g = false;
            timer4.Enabled = false;
            if (!g && !vg) igrac++;
            else golman++;
            label3.Text = Convert.ToString(golman);
            label4.Text = Convert.ToString(igrac);
            timer3.Enabled = true;
            System.Threading.Thread.Sleep(800);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (golman == 5 || igrac == 5)
            {
                golman = 0;
                igrac = 0;
            }
            label3.Text = Convert.ToString(golman);
            label4.Text = Convert.ToString(igrac);
            sut = 0;                                               
            timer3.Enabled = false;
            timer1.Enabled = true;
        }


    }
}
