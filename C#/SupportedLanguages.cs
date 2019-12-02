// Michael Coughlin
// hiimmichael.com
// 2019

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Test
{

    public class SupportedLanguages : Enumeration
    {
        public static SupportedLanguages english = new SupportedLanguages(1, "English");
        public static SupportedLanguages spanish = new SupportedLanguages(2, "Español");
        public static SupportedLanguages french = new SupportedLanguages(3, "Français");
        public static SupportedLanguages german = new SupportedLanguages(4, "Deutsche");
        public static SupportedLanguages italian = new SupportedLanguages(5, "Italiano");
        public static SupportedLanguages polish = new SupportedLanguages(6, "Polskie");
        public static SupportedLanguages russian = new SupportedLanguages(7, "Pусский");
        public static SupportedLanguages portuguese = new SupportedLanguages(8, "Português");

        public SupportedLanguages() { }

        public SupportedLanguages(int id, string name)
            : base(id, name)
        {
        }

        public IEnumerable<SupportedLanguages> List()
        {
            return new[] {english, spanish, french, german, italian, polish, russian, portuguese};
        }
    }
}
