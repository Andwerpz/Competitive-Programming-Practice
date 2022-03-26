//package cowoperations;

import java.util.*;
import java.io.*;

public class cowoperations {
	public static void main(String[] args) throws IOException {
		
		//2022 March USACO Silver 
		
		//the operations given to you are as follows: 
		//1. you may remove 2 consecutive equal characters
		//2. you may replace a character with the other 2 in either order
		
		//from these two, we can derive 3 more operations:
		//3. you may remove 2 unequal consecutive characters and replace it with the other character
		//4. you may insert 2 equal characters anywhere you like
		//5. you can reverse the order of any 2 characters
		
		//3 was shown in the problem statement: OW -> CWW -> C
		//4: C -> OW -> CWW
		//5 can be shown with the use of 3: OW -> C -> WO
		
		//given 5, we can notice that the order of the characters within the given string are irrelevant.
		
		//the most straightforward approach of reducing a string is to first reduce all the Os and Ws down to Cs. 
		
		//if the difference between Os and Ws is odd, then we can never reduce them all down into Cs; at least one
		//O or W will be left in the string. 
		
		//once we reduce everything down into Cs, if there is an even amount, then the string is invalid. Notice that 
		//we can never add an odd amount of Cs to the string using the operations. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		char[] s = fin.readLine().toCharArray();
		int q = Integer.parseInt(fin.readLine());
		int[] c = new int[s.length + 1];
		int[] o = new int[s.length + 1];
		int[] w = new int[s.length + 1];
		for(int i = 0; i < s.length; i++) {
			if(s[i] == 'C') {
				c[i + 1] ++;
			}
			else if(s[i] == 'O') {
				o[i + 1] ++;
			}
			else {
				w[i + 1] ++;
			}
			c[i + 1] += c[i];
			o[i + 1] += o[i];
			w[i + 1] += w[i];
			//System.out.println(c[i + 1] + " " + o[i + 1] + " " + w[i + 1]);
		}
		StringBuilder fout = new StringBuilder();
		while(q-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int l = Integer.parseInt(st.nextToken()) - 1;
			int r = Integer.parseInt(st.nextToken());
			int cCnt = c[r] - c[l];
			int oCnt = o[r] - o[l];
			int wCnt = w[r] - w[l];
			//System.out.println(cCnt + " " + oCnt + " " + wCnt);
			boolean isValid = false;
			if(Math.abs(wCnt - oCnt) % 2 == 0 && (cCnt + oCnt) % 2 == 1) {
				isValid = true;
			}
			fout.append(isValid? "Y" : "N");
		}
		System.out.print(fout);
	}
}
