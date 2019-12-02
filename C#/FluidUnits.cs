// Michael Coughlin
// hiimmichael.com
// 2019

using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace Test {
    public class FluidUnits : Enumeration {
        public static FluidUnits pints = new FluidUnits(1, "Pints");
        public static FluidUnits quarts = new FluidUnits(2, "Quarts");
        public static FluidUnits gallons = new FluidUnits(3, "Gallons");
        public static FluidUnits liters = new FluidUnits(4, "Liters");

        public FluidUnits() { }

        public FluidUnits(int id, string name)
            : base(id, name) {
        }

        public IEnumerable<FluidUnits> List() {
            return new[] { pints, quarts, gallons, liters };
        }

        public double convertAmountToPints(string amount, string units) {
            double result = 0.0;

            switch (units) {
                case "Pints":
                    result = Convert.ToDouble(amount);
                    break;
                case "Quarts":
                    result = Convert.ToDouble(amount) * 2;
                    break;
                case "Gallons":
                    result = Convert.ToDouble(amount) * 8;
                    break;
                case "Liters":
                    result = Convert.ToDouble(amount) * 2.113376;
                    break;
            }
            return result;
        }

        internal void convertPintsToDefaultUnits(DataGridViewCell dataGridViewCell, string units) {
            switch (units) {
                case "Pints":
                    break;
                case "Quarts":
                    dataGridViewCell.Value = Convert.ToDouble(dataGridViewCell.Value) * 0.5;
                    break;
                case "Gallons":
                    dataGridViewCell.Value = Convert.ToDouble(dataGridViewCell.Value) * 0.125;
                    break;
                case "Liters":
                    dataGridViewCell.Value = Convert.ToDouble(dataGridViewCell.Value) * 0.473176;
                    break;
            }
        }

        internal string convertPintsToDefaultUnits(string total, string units) {
            double result = 0.0;

            switch (units) {
                case "Pints":
                    result = Convert.ToDouble(total);
                    break;
                case "Quarts":
                    result = Convert.ToDouble(total) * 0.5;
                    break;
                case "Gallons":
                    result = Convert.ToDouble(total) * 0.125;
                    break;
                case "Liters":
                    result = Convert.ToDouble(total) * 0.473176;
                    break;
            }
            return Convert.ToString(result);
        }
    }
}
