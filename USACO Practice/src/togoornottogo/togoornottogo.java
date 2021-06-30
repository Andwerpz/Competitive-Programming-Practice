//package togoornottogo;

import java.util.*;
import java.io.*;
 
public class togoornottogo {
	
	static StreamTokenizer fin;
	
	public static int nextInt() throws IOException {
		fin.nextToken();
		return (int) fin.nval;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1520G
		
		FastIO io = new FastIO();
		//fin = new StreamTokenizer(new BufferedReader(new InputStreamReader(System.in)));
		int n = io.nextInt();
		int m = io.nextInt();
		int w = io.nextInt();
		int[][] g = new int[n][m];
		long[][] dp = new long[n][m];
		ArrayList<int[]> portals = new ArrayList<int[]>();
		for(int i = 0; i < n; i++) {
			Arrays.fill(dp[i], Long.MAX_VALUE / 2);
		}
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				g[i][j] = io.nextInt();
				if(g[i][j] > 0) {
					portals.add(new int[] {i, j, g[i][j]});
				}
			}
		}
		dp[0][0] = 0;
		ArrayDeque<Integer> qx = new ArrayDeque<Integer>();
		ArrayDeque<Integer> qy = new ArrayDeque<Integer>();
		qx.add(0);
		qy.add(0);
		int[] xDiff = new int[] {0, 0, 1, -1};
		int[] yDiff = new int[] {1, -1, 0, 0};
		boolean portalUsed = false;
		while(qx.size() != 0) {
			int x = qx.poll();
			int y = qy.poll();
			long cost = dp[x][y] + w;
			for(int i = 0; i < 4; i++) {
				int nextX = x + xDiff[i];
				int nextY = y + yDiff[i];
				if(nextX != n && nextX != -1 && nextY != m && nextY != -1) {
					if(g[nextX][nextY] >= 0 && dp[nextX][nextY] > cost) {
						dp[nextX][nextY] = cost;
						qx.add(nextX);
						qy.add(nextY);
					}
				}
			}
			if(qx.size() == 0 && !portalUsed) {	//use the portal with the least cost
				//System.out.println("PORTAL USED");
				portalUsed = true;
				long minCost = Long.MAX_VALUE / 2;
				int index = -1;
				for(int i = 0; i < portals.size(); i++) {
					if(dp[portals.get(i)[0]][portals.get(i)[1]] + portals.get(i)[2] < minCost) {
						minCost = dp[portals.get(i)[0]][portals.get(i)[1]] + portals.get(i)[2];
						index = i;
					}
				}
				//System.out.println("PORTAL: " + index);
				//System.out.println("COST: " + minCost);
				if(index != -1) {
					for(int i = 0; i < portals.size(); i++) {
						int px = portals.get(i)[0];
						int py = portals.get(i)[1];
						long portalCost = minCost + portals.get(i)[2];
						//System.out.println(dp[px][py]);
						if(dp[px][py] > portalCost) {
							dp[px][py] = portalCost;
							qx.add(px);
							qy.add(py);
						}
						
					}
				}
			}
//			cost = dp[x][y];
//			if(g[x][y] > 0) {	//portal
//				for(int i = 0; i < portals.size(); i++) {
//					int px = portals.get(i)[0];
//					int py = portals.get(i)[1];
//					if(px != x || py != y) {
//						long portalCost = g[x][y] + portals.get(i)[2] + cost;
//						if(dp[px][py] > portalCost) {
//							dp[px][py] = portalCost;
//							s.add(new ArrayList<Integer>(Arrays.asList(px, py)));
//						}
//					}
//				}
//			}
//			for(long[] i : dp) {
//				for(long j : i) {
//					System.out.print(((j == Integer.MAX_VALUE)? "#" : j) + " ");
//				}
//				System.out.println();
//			}
//			System.out.println();
		}
//		for(long[] i : dp) {
//			for(long j : i) {
//				System.out.print(((j == Integer.MAX_VALUE)? "#" : j) + " ");
//			}
//			System.out.println();
//		}
		if(dp[n - 1][m - 1] == Long.MAX_VALUE / 2) {
			System.out.println(-1);
		}
		else {
			System.out.println(dp[n - 1][m - 1]);
		}
	}
}

class FastIO extends PrintWriter {
	private InputStream stream;
	private byte[] buf = new byte[1<<16];
	private int curChar, numChars;

	// standard input
	public FastIO() { this(System.in,System.out); }
	public FastIO(InputStream i, OutputStream o) {
		super(o);
		stream = i;
	}
	// file input
	public FastIO(String i, String o) throws IOException {
		super(new FileWriter(o));
		stream = new FileInputStream(i);
	}

	// throws InputMismatchException() if previously detected end of file
	private int nextByte() {
		if (numChars == -1) throw new InputMismatchException();
		if (curChar >= numChars) {
			curChar = 0;
			try {
				numChars = stream.read(buf);
			} catch (IOException e) {
				throw new InputMismatchException();
			}
			if (numChars == -1) return -1; // end of file
		}
		return buf[curChar++];
	}

	// to read in entire lines, replace c <= ' '
	// with a function that checks whether c is a line break
	public String next() {
		int c; do { c = nextByte(); } while (c <= ' ');
		StringBuilder res = new StringBuilder();
		do { res.appendCodePoint(c); c = nextByte(); } while (c > ' ');
		return res.toString();
	}
	public int nextInt() { // nextLong() would be implemented similarly
		int c; do { c = nextByte(); } while (c <= ' ');
		int sgn = 1; if (c == '-') { sgn = -1; c = nextByte(); }
		int res = 0;
		do {
			if (c < '0' || c > '9')
				throw new InputMismatchException();
			res = 10*res+c-'0';
			c = nextByte();
		} while (c > ' ');
		return res * sgn;
	}
	public double nextDouble() { return Double.parseDouble(next()); }
}