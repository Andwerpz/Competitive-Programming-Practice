//package prefixfliphardversion;

import java.util.*;
import java.io.*;

public class prefixfliphardversion {
	public static void main(String[] args) throws IOException {
		
		//1381A2
		
		//this problem is pretty interesting. you have to constantly flip the bits, and figure out how to deal with it in linear time.
		
		//Notice that you can just worry about the last bit. First, get the last bit correct, then move on to the second last bit. When getting the second to last bit correct, 
		//you won't change the last bit. So you can go from right to left, changing the bits one by one, using a maximum of 2 moves on each bit. 
		
		//the tricky part is saving the information on the bits when you flip them. Obviously, you can't go and change all the bits, that would take time on the order of n^2. 
		//The method used here is saving the 'active' segment. The 'active' segment is the segment that we are flipping. Everything outside of the 'active' segment is set. 
		//we keep track of the active segment using two pointers, denoting the boundaries, and a boolean denoting whether the segment has been flipped and inverted. 
		//since we are only worrying about the edges, we can just refer to the bits on the boundaries.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			boolean[] a = new boolean[n];
			boolean[] b = new boolean[n];
			char[] s = fin.readLine().toCharArray();
			for(int i = 0; i < n; i++) {
				a[i] = s[i] == '1';
			}
			s = fin.readLine().toCharArray();
			for(int i = 0; i < n; i++) {
				b[i] = s[i] == '1';
			}
			StringBuilder cur = new StringBuilder();
			int amt = 0;
			boolean reversed = false;
			int left = 0;
			int right = n - 1;
			for(int i = n - 1; i >= 0; i--) {
				if(!reversed? a[right] != b[i] : a[left] == b[i]) {
					if(!reversed) {
						if(a[left] == b[i]) {
							amt ++;
							cur.append(1).append(" ");
						}
						amt ++;
						cur.append(i + 1).append(" ");
						left ++;
						reversed = !reversed;
					}
					else {
						if(a[right] != b[i]) {
							amt ++;
							cur.append(1).append(" ");
						}
						amt ++;
						cur.append(i + 1).append(" ");
						right --;
						reversed = !reversed;
					}
				}
				else {
					if(!reversed) {
						right --;
					}
					else {
						left ++;
					}
				}
			}
			fout.append(amt).append(" ");
			fout.append(cur);
			fout.append("\n");
		}
		System.out.print(fout);
	}
}
