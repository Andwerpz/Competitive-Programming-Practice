//package strangetest;

import java.util.*;
import java.io.*;

public class strangetest {
	public static void main(String[] args) throws IOException {
		
		//1632C
		
		//can be solved with a rather brute force approach
		
		//for a given b value, find out how many moves it takes just changing a to get a to b. 
		
		//notice that a < b. So if you can't change b, then it makes sense that if you apply a|b operation, you would
		//want to make sure that after the operation, a == b, since if it doesn't, then a > b. 
		
		//figuring out how much you need to add to a isn't that hard. 
		
		//do this for every b value, until the amount you need to add to a to make a|b == b, 0.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int a = Integer.parseInt(st.nextToken());
			int b = Integer.parseInt(st.nextToken());
			int count = 0;
			int ans = Integer.MAX_VALUE;
			while(true) {
				//check for current cost
				char[] sa = Integer.toBinaryString(a).toCharArray();
				char[] sb = Integer.toBinaryString(b).toCharArray();
				
				int pb = 0;
				int pa = 0 - (sb.length - sa.length);
				boolean same = true;
				while(pb != sb.length) {
					char aVal = pa < 0? '0' : sa[pa];
					char bVal = sb[pb];
					if(aVal == '1' && bVal == '0') {	//find the next largest bit in b that a doesn't have
						while(true) {
							pb --;
							pa --;
							if(sb[pb] == '1' && (pa < 0 || sa[pa] == '0')) {
								break;
							}
						}
						same = false;
						break;
					}
					pb ++;
					pa ++;
				}
				if(same) {
					ans = Math.min(count + 1, ans);
					break;
				}
				int aSum = 0;
				int bSum = (int) Math.pow(2, (sb.length - 1) - pb);
				int pow = 1;
				for(int i = sa.length - 1; i >= pa; i--) {
					char aVal = i < 0? '0' : sa[i];
					if(aVal == '1') {
						aSum += pow;
					}
					pow *= 2;
				}
//				if(count + (bSum - aSum) + (pb == 0? 0 : 1) < ans) {
//					System.out.println("COUNT: " + count);
//					System.out.println(pa + " " + pb);
//					System.out.println(String.valueOf(sa) + " " + String.valueOf(sb) + " " + aSum + " " + bSum + " " + sa.length + " " + sb.length);
//				}
				int curAns = count + (bSum - aSum);
				if(a + (bSum - aSum) != b) {
					curAns ++;
				}
				ans = Math.min(curAns, ans);
//				if((count + (bSum - aSum)) < 0) {
//					System.out.println("A: " + (count + (bSum - aSum)));
//					System.out.println(String.valueOf(sa) + " " + String.valueOf(sb) + " " + aSum + " " + bSum + " " + sa.length + " " + sb.length);
//				}
				
				count ++;
				b ++;
				//System.out.println(b);
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
