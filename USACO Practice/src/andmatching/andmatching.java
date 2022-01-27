//package andmatching;

import java.util.*;
import java.io.*;

public class andmatching {
	public static void main(String[] args) throws IOException {
		
		//1631C
		
		//first notice that if k == 0, then we can always make it. Consider n = 8.
		
		//0 0 0
		//1 0 0
		//0 1 0
		//1 1 0
		//0 0 1
		//1 0 1
		//0 1 1
		//1 1 1
		
		//see that the top and the bottom are opposites in terms of bits. Same goes for 1 and 6, 2 and 5 and so on. This is just a 
		//property of binary counting. If we form pairs from these opposites, we can always get a sum of 0;
		
		//now consider when k != 0. Since we are doing bitwise operations, we should probably make use of the powers of 2 to make k:
		//2^0, 2^1, 2^2, ect.. 
		
		//notice that these powers of 2 only have 1 bit with value '1', and that their opposites only have 1 '0' bit. 
		
		//lets say that k has more than 1 '1' bit, for example 5: 101. Expressing this number as the sum of single '1' value
		//binary numbers would be: 100 + 001 = 101. Lets label these single '1' values 'A' and their opposites 'B'.
		
		//0 0 0
		//1 0 0		A1
		//0 1 0
		//1 1 0		B2
		//0 0 1		A2
		//1 0 1
		//0 1 1		B1
		//1 1 1
		
		//notice that the A1 & B2 == A1. In the general case, as long as you pair an A value with an opposite of another A value, 
		//then the bitwise and will always equal the original A value
		
		//one special case is where k is a power of 2. In this case, pair the A value with n - 1, because n - 1 & A == A. Then you can just 
		//pair B with 0, resulting in 0, and pair everything else with their opposite. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int k = Integer.parseInt(st.nextToken());
			if(n == 4) {
				if(k == 3) {
					fout.append("-1\n");
				}
				else if(k == 0) {
					fout.append("0 3\n1 2\n");
				}
				else if(k == 1) {
					fout.append("1 3\n2 0\n");
				}
				else {
					fout.append("2 3\n1 0\n");
				}
				continue;
			}
			HashSet<Integer> v = new HashSet<Integer>();
			ArrayList<int[]> pairs = new ArrayList<int[]>();
			char[] s = Integer.toBinaryString(k).toCharArray();
			//System.out.println(s);
			int pow = 1;
			for(int i = s.length - 1; i >= 0; i--) {
				char c = s[i];
				if(c == '1') {
					v.add(pow);
					v.add(n - 1 - pow);
					pairs.add(new int[] {pow, n - 1 - pow});
				}
				pow *= 2;
			}
			if(pairs.size() > 1) {
				for(int i = 0; i < pairs.size(); i++) {
					//match current a to next b
					fout.append(pairs.get(i)[0]).append(" ").append(pairs.get((i + 1) % pairs.size())[1]).append("\n");
				}
			}
			else if(pairs.size() != 0){
				v.add(0);	v.add(n - 1);
				fout.append(pairs.get(0)[0]).append(" ").append(n - 1).append("\n0 ").append(pairs.get(0)[1]).append("\n");
			}
			//match all other numbers symmetrically
			int l = 0;
			int h = n - 1;
			while(v.contains(l)) {
				l ++;
			}
			while(v.contains(h)) {
				h --;
			}
			while(true) {
				fout.append(l).append(" ").append(h).append("\n");
				l++;
				h--;
				while(v.contains(l)) {
					l ++;
				}
				while(v.contains(h)) {
					h --;
				}
				if(l >= h) {
					break;
				}
			}
		}
		System.out.print(fout);
	}
}
