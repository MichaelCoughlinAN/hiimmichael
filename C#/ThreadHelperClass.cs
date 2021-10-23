// Michael Coughlin
// hiimmichael.com
// 2019

using System.Drawing;
using System.Windows.Forms;

namespace Test {
    public static class ThreadHelperClass {
        delegate void SetTextCallback(Form f, Control ctrl, string text);
        delegate void SetImageCallback(Form f, Button ctrl, Bitmap image);

        /// <summary>
        /// Set text property of various controls
        /// </summary>
        /// <param name="form">The calling form</param>
        /// <param name="ctrl"></param>
        /// <param name="text"></param>
        public static void SetText(Form form, Control ctrl, string text) {
            // InvokeRequired required compares the thread ID of the 
            // calling thread to the thread ID of the creating thread. 
            // If these threads are different, it returns true. 
            if (ctrl.InvokeRequired) {
                SetTextCallback d = new SetTextCallback(SetText);
                form.Invoke(d, new object[] { form, ctrl, text });
            } else {
                ctrl.Text = text;
            }
        }

        public static void SetImage(Form form, Button ctrl, Bitmap image) {
            if (ctrl.InvokeRequired) {
                SetImageCallback d = new SetImageCallback(SetImage);
                form.Invoke(d, new object[] { form, ctrl, image });
            } else {
                ctrl.Image = image;
            }
        }
    }
}
