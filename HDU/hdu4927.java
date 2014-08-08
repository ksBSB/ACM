import java.util.Scanner;
import java.math.BigInteger;

public class Main {
	public static void main(String[] args) { 
		Scanner cin =  new Scanner(System.in); 

		BigInteger[] a;
		a = new BigInteger[3005];

		int cas, n;
		cas	= cin.nextInt();;

		for (int k = 0; k < cas; k++) {
			n = cin.nextInt();

			for (int i = 0; i < n; i++)
				a[i] = cin.nextBigInteger();
			BigInteger ans = BigInteger.valueOf(0);
			BigInteger c = BigInteger.valueOf(1);;

			for (int i = 0; i < n; i++) {
				BigInteger tmp = c.multiply(a[n-i-1]);

				if (i%2 == 0)
					ans = ans.add(tmp);
				else
					ans = ans.subtract(tmp);

				tmp = c.multiply(BigInteger.valueOf(n-i-1));
				c = tmp.divide(BigInteger.valueOf(i+1));
			}

			System.out.println(ans);
		}
	} 
}
