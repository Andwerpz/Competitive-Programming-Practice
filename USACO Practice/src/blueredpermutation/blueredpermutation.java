//package blueredpermutation;

import java.util.*;
import java.io.*;

public class blueredpermutation {
	public static void main(String[] args) throws IOException {
		
		//1607D
		
		//you can deal with the blue and red groups of numbers separately. 
		
		//notice that for the blue group, since you can only decrease the numbers, it makes sense that the blue group should occupy the lower 
		//part of the permutation. Same for the red group, it just occupies the upper part. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			int[] nums = new int[n];
			StringTokenizer st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
			}
			char[] color = fin.readLine().toCharArray();
			ArrayList<Integer> blue = new ArrayList<Integer>();
			ArrayList<Integer> red = new ArrayList<Integer>();
			for(int i = 0; i < n; i++) {
				if(color[i] == 'R') {
					red.add(nums[i]);
				}
				else {
					blue.add(nums[i]);
				}
			}
			blue.sort((a, b) -> Integer.compare(a, b));
			red.sort((a, b) -> -Integer.compare(a, b));
			boolean isValid = true;
			for(int i = 0; i < blue.size(); i++) {
				int next = blue.get(i);
				if(next < i + 1) {
					isValid = false;
					break;
				}
			}
			for(int i = 0; i < red.size(); i++) {
				int next = red.get(i);
				if(next > n - i) {
					isValid = false;
					break;
				}
			}
			fout.append(isValid? "YES\n" : "NO\n");
		}
		System.out.print(fout);
	}
}
