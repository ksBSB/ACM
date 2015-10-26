import java.util.*;
import java.math.*;
import java.io.*;

public class Main {
	final static int maxn = 1000000;  

	static int cnt = 0;
	static int vis[] = new int[maxn+5];
	static int pri[] = new int[maxn+5];

	public static void main(String args[]) {
		Scanner cin = new Scanner(System.in);
		Arrays.fill(vis, 0);  

		for (int i = 2; i <= maxn; i++) {
			if (vis[i] == 1) continue;
			pri[cnt++] = i;
			for (int j = i + i; j <= maxn; j += i)
				vis[j] = 1;
		}

		int cas = cin.nextInt();
		BigInteger k[] = new BigInteger[3];

		while (cas-- > 0) {
			for (int i = 0; i < 2; i++)
				k[i] = cin.nextBigInteger();

			k[2] = k[0].gcd(k[1]);
			long ans[] = new long[3];

			for (int i = 0; i < 3; i++) {
				ans[i] = 1;
				for (int j = 0; j < cnt; j++) {
					if (k[i].mod(BigInteger.valueOf(pri[j])).equals(BigInteger.ZERO)) {
						long c = 0;
						while (k[i].mod(BigInteger.valueOf(pri[j])).equals(BigInteger.ZERO)) {
							k[i] = k[i].divide(BigInteger.valueOf(pri[j]));
							c++;
						}
						ans[i] *= c;
					}
				}
			}

			if(k[2].compareTo(BigInteger.valueOf(maxn))==1) {
				long n = solve(k[2]);

				BigInteger g;
				if (n == 1)
					g = k[2];
				else if (n == 2) {
					g = BigInteger.valueOf((long)Math.sqrt(k[2].doubleValue()));
					if (!k[2].equals(g.multiply(g)))
						g = g.add(BigInteger.ONE);
				} else {
					g = BigInteger.valueOf((long)Math.pow(k[2].doubleValue(), 1.0/3));
					if (!k[2].equals(g.multiply(g.multiply(g))));
					g = g.add(BigInteger.ONE);
				}

				for (int i = 0; i < 2; i++) {
					long c = 0;
					while (k[i].mod(g).equals(BigInteger.ZERO)) {
						k[i] = k[i].divide(g);
						c++;
					}
					ans[i] *= c;

					if (k[i].compareTo(BigInteger.valueOf(maxn)) == 1)
						ans[i] *= solve(k[i]);
				}
			}

			System.out.println(ans[0] + " " + ans[1]);
		}
	}

	static long solve(BigInteger k) {
		if (k.equals(BigInteger.ONE)) return 1;

		BigInteger a = BigInteger.valueOf((long)Math.sqrt(k.doubleValue()));
		if (k.equals(a.multiply(a))) return 2;
		a = a.add(BigInteger.ONE);
		if (k.equals(a.multiply(a))) return 2;

		BigInteger b = BigInteger.valueOf((long)Math.pow(k.doubleValue(), 1.0/3));
		if (k.equals(b.multiply(b.multiply(b)))) return 3;
		b = b.add(BigInteger.ONE);
		if (k.equals(b.multiply(b.multiply(b)))) return 3;

		return 1;
	}
}
