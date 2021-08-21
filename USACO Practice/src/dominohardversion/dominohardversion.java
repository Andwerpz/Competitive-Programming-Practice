//package dominohardversion;

import java.util.*;
import java.io.*;

public class dominohardversion {
	
	public static StringBuilder getAns1(int n, int m, int k) {
		StringBuilder ans = new StringBuilder();
		char[][] s = new char[n][m];
		for(int i = 0; i < n; i += 2) {
			for(int j = 0; j < m; j += 2) {
				if(k > 0) {
					char nextChar = getNextChar(s, i, j, i, j + 1);
					s[i][j] = nextChar;
					s[i][j + 1] = nextChar;
					nextChar = getNextChar(s, i + 1, j, i + 1, j + 1);
					s[i + 1][j] = nextChar;
					s[i + 1][j + 1] = nextChar;
					k -= 2;
				}
				else {
					char nextChar = getNextChar(s, i, j, i + 1, j);
					s[i][j] = nextChar;
					s[i + 1][j] = nextChar;
					nextChar = getNextChar(s, i, j + 1, i + 1, j + 1);
					s[i][j + 1] = nextChar;
					s[i + 1][j + 1] = nextChar;
				}
			}
		}
		for(char[] i : s) {
			for(char j : i) {
				ans.append(j);
			}
			ans.append("\n");
		}
		return ans;
	}
	
	public static StringBuilder getAns2(int n, int m, int k, boolean reverse) {
		StringBuilder ans = new StringBuilder();
		char[][] s = new char[n][m];
		for(int i = 0; i < m; i += 2) {
			char nextChar = getNextChar(s, 0, i, 0, i + 1);
			s[0][i] = nextChar;
			s[0][i + 1] = nextChar;
		}
		for(int i = 1; i < n; i += 2) {
			for(int j = 0; j < m; j += 2) {
				if(k > 0) {
					char nextChar = getNextChar(s, i, j, i, j + 1);
					s[i][j] = nextChar;
					s[i][j + 1] = nextChar;
					nextChar = getNextChar(s, i + 1, j, i + 1, j + 1);
					s[i + 1][j] = nextChar;
					s[i + 1][j + 1] = nextChar;
					k -= 2;
				}
				else {
					char nextChar = getNextChar(s, i, j, i + 1, j);
					s[i][j] = nextChar;
					s[i + 1][j] = nextChar;
					nextChar = getNextChar(s, i, j + 1, i + 1, j + 1);
					s[i][j + 1] = nextChar;
					s[i + 1][j + 1] = nextChar;
				}
			}
		}
		if(!reverse) {
			for(char[] i : s) {
				for(char j : i) {
					ans.append(j);
				}
				ans.append("\n");
			}
		}
		else {
			for(int i = 0; i < m; i++) {
				for(int j = 0; j < n; j++) {
					ans.append(s[j][i]);
				}
				ans.append("\n");
			}
		}
		return ans;
	}
	
	public static char getNextChar(char[][] s, int r1, int c1, int r2, int c2) {
		HashSet<Character> dict = new HashSet<Character>();
		int[][] coords = new int[][] {{r1, c1}, {r2, c2}};
		int[] dx = new int[] {1, -1, 0, 0};
		int[] dy = new int[] {0, 0, 1, -1};
		for(int i = 0; i < dx.length; i++) {
			for(int j = 0; j < coords.length; j++) {
				int x = coords[j][0];
				int y = coords[j][1];
				int diffX = dx[i];
				int diffY = dy[i];
				if(diffX + x >= 0 && diffX + x < s.length && diffY + y >= 0 && diffY + y < s[0].length) {
					dict.add(s[diffX + x][diffY + y]);
				}
			}
		}
		for(char i = 'a'; i <= 'z'; i++) {
			if(!dict.contains(i)) {
				return i;
			}
		}
		return 'a';
	}
	
	public static void main(String[] args) throws IOException {
		
		//1551D2
		
		//this problem is pretty much 1551D1 except much more tedious.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int m = Integer.parseInt(st.nextToken());
			int k = Integer.parseInt(st.nextToken());
			int total = n * m;
			total /= 2;
			if(n % 2 == 0 && m % 2 == 0) {
				if(k % 2 == 0) {
					fout.append("YES\n");
					fout.append(getAns1(n, m, k));
				}
				else {
					fout.append("NO\n");
				}
			}
			else {
				boolean reverse = false;
				if(m % 2 == 1) {
					int temp = n;
					n = m;
					m = temp;
					k = total - k;
					reverse = true;
				}
				if(k < m / 2) {
					fout.append("NO\n");
				}
				else {
					k -= m / 2;
					if(k % 2 == 0) {
						fout.append("YES\n");
						fout.append(getAns2(n, m, k, reverse));
					}
					else {
						fout.append("NO\n");
					}
				}
			}
		}
		System.out.print(fout);
	}
}
