using System;

namespace BottomUp_Automatic_Differentiation
{
    class MainClass
    {
        public static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");
            BottomUpAutoDiffTest();
        }

        public static void BottomUpAutoDiffTest()
        {
            var x = new BottomUpAutoDiff(Math.PI / 4, 1.0);
            var y = BottomUpAutoDiff.sin(x);

            // sin(x)の微分 
            //x.setValue(Math.PI / 4);
            //x.select();
            //y = Math.Sin(x);
            Console.WriteLine(2 * y.getdVal());

            var x2 = new BottomUpAutoDiff(5.0, 1.0);
            var y2 = new BottomUpAutoDiff(1.0, 1.0);
            //x = 5.0;
            //y = 0.0;
            //x.select();
            for (int i = 0; i < 10; ++i) y2 = y2 + x2 * x2;
            // x = 5.0のときのyとdy/dxを出力
            Console.WriteLine("{0}, {1}", y2.getValue(), y2.getdVal());

            // ニュートン法の実行
            var x3 = new BottomUpAutoDiff(2.0, 1.0);
            var y3 = new BottomUpAutoDiff(0.0, 1.0);
            //x = 2.0; // 適当な初期値
            for (int i = 0; i < 10000; ++i)
            {
                // y = (x-sqrt(2))*(x^2+x+1)
                y3.setValue((x3.getValue() - Math.Sqrt(2.0)));// * 
                            //(x3.getValue() * x3.getValue() + x3.getValue() + 1));
                // yの値がdoubleの丸め誤差と同程度に小さければ終了
                if (y3.getValue() < 1e-15) break;
                // ニュートン法の更新式で次のxを求める
                x3.setValue(x3.getValue() - y3.getValue() / y3.getdVal());
            }
            // x(=sqrt(2))を出力
            Console.WriteLine(x3.getValue());
        }
    }
}
