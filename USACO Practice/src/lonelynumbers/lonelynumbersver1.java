package lonelynumbers;

import java.util.*;
import java.io.*;

public class lonelynumbersver1 {
	
	public static boolean isLonely(int a, int b) {
		int gcd = gcd(a, b);
		int sideA = gcd;
		int sideB = a / gcd;
		int sideC = b / gcd;
		if(sideA + sideB > sideC && sideB + sideC > sideA && sideC + sideA > sideB) {
			return false;
		}
		return true;
	}
	
	public static int gcd(int a, int b) {
		if(b == 0) {
			return a;
		}
		return gcd(b, a % b);
	}
	
	public static void main(String[] args) throws IOException {
		
		//1423K
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int[] dict = new int[100];
		dict[0] = 1;
		HashSet<Integer> lonely = new HashSet<Integer>();	//1 is always a lonely number, but we don't include it in the set.
		for(int i = 1; i < dict.length; i++) {
			int next = i + 1;
			HashSet<Integer> nextSet = new HashSet<Integer>();
			boolean isLonely = true;
			for(int j : lonely) {
				if(!isLonely(j, next)) {
					isLonely = false;
				}
				else {
					nextSet.add(j);
				}
			}
			if(isLonely) {
				nextSet.add(next);
			}
			lonely = nextSet;
			dict[i] = lonely.size() + 1;
			System.out.println(i + " " + lonely);
		}
		StringBuilder fout = new StringBuilder();
		int t = Integer.parseInt(fin.readLine());
		StringTokenizer st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < t; i++) {
			fout.append(dict[Integer.parseInt(st.nextToken()) - 1]).append(" ");
		}
		System.out.println(fout);
	}
}
