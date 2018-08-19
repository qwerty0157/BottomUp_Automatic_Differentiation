using System;
namespace BottomUp_Automatic_Differentiation
{
    public class BottomUpAutoDiff
    {
        double val;
        double dVal;

        public BottomUpAutoDiff(double v = 0.0, double dv = 0.0)
        {
            this.val = v;
            this.dVal = dv;
        }

        public void select()
        {
            dVal = 1.0;
        }

        public void setValue(double v)
        {
            this.val = v;
        }

        public void setdVal(double v)
        {
            this.dVal = v;
        }
        public double getValue()
        {
            return val;
        }

        public double getdVal()
        {
            return dVal;
        }

        //operator
        public static BottomUpAutoDiff operator+ (BottomUpAutoDiff x, BottomUpAutoDiff y) 
        {
            return new BottomUpAutoDiff(x.val+y.val, x.dVal+y.dVal);
        }
    
        public static BottomUpAutoDiff operator- (BottomUpAutoDiff x, BottomUpAutoDiff y)
        {
            return new BottomUpAutoDiff(x.val - y.val, x.dVal - y.dVal);
        }
        public static BottomUpAutoDiff operator* (BottomUpAutoDiff x, BottomUpAutoDiff y)
        {
            return new BottomUpAutoDiff(x.val * y.val, x.dVal * y.val + x.val * y.dVal);
        }
        public static BottomUpAutoDiff operator/ (BottomUpAutoDiff x, BottomUpAutoDiff y)
        {
            double w = x.val / y.val;
            return new BottomUpAutoDiff(w, (x.dVal - w * y.dVal) / y.val);
        }
        public static BottomUpAutoDiff operator+ (BottomUpAutoDiff x)
        {
            return new BottomUpAutoDiff(x.val, x.dVal);
        }
        public static BottomUpAutoDiff operator- (BottomUpAutoDiff x)
        {
            return new BottomUpAutoDiff(-x.val, -x.dVal);
        }
        public static bool operator< (BottomUpAutoDiff x, BottomUpAutoDiff y)
        {
            return x.val < y.val;
        }
        public static bool operator<= (BottomUpAutoDiff x, BottomUpAutoDiff y)
        {
            return x.val <= y.val;
        }
        public static bool operator> (BottomUpAutoDiff x, BottomUpAutoDiff y)
        {
            return x.val > y.val;
        }
        public static bool operator>= (BottomUpAutoDiff x, BottomUpAutoDiff y)
        {
            return x.val >= y.val;
        }

        public static BottomUpAutoDiff sqrt(BottomUpAutoDiff x)
        {
            return new BottomUpAutoDiff(Math.Sqrt(x.val), 0.5 * x.dVal / Math.Sqrt(x.val));
        }
        public static BottomUpAutoDiff exp(BottomUpAutoDiff x)
        {
            return new BottomUpAutoDiff(Math.Exp(x.val), x.dVal * Math.Exp(x.val));
        }
        public static BottomUpAutoDiff log(BottomUpAutoDiff x)
        {
            return new BottomUpAutoDiff(Math.Log(x.val), x.dVal / x.val);
        }
        public static BottomUpAutoDiff sin(BottomUpAutoDiff x)
        {
            return new BottomUpAutoDiff(Math.Sin(x.val), Math.Cos(x.val));
        }
        public static BottomUpAutoDiff cos(BottomUpAutoDiff x)
        {
            return new BottomUpAutoDiff(Math.Cos(x.val), -Math.Sin(x.val));
        }

    }
}
