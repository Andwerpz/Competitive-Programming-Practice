package arraypartition;

import java.util.*;
import java.io.*;

public class arraypartitionver2 {
	public static void main(String[] args) throws IOException {
		
		//1454F
		
				//get the number of occurrences of the maximum number in the array. If the number of occurrences is greater than or equal to 3, then you can easily partition the array, with the middle partition
				//having one occurrence of the maximum, and the other two will be guaranteed to be equal to the maximum, since there are two more.
				
				//if not, then there are 1 or two occurrences of the maximum number, and these must be in the middle segment, since putting them in the left or right segments will make it so that the middle
				//segment will always be less than them. So the middle segment at minimum must include all maximum values.
				
				//to expand the middle segment, we can either expand it left or right. Since we get to choose, we always want to expand in the direction where the minimum of the values of the three
				//segments is the most. This makes it so that we get the most chances to make them equal.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int[] nums = new int[n];
			int max = 0;
			int numMax = 0;
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
				if(nums[i] > max) {
					numMax = 1;
					max = nums[i];
				}
				else if(nums[i] == max) {
					numMax ++;
				}
			}
			if(numMax == n) {
				fout.append("YES\n1 1 ").append(n - 2).append("\n");
				continue;
			}
			int l = 0;
			int r = n - 1;
			boolean isValid = true;
			if(numMax >= 3) {
				boolean seenMax = false;
				int pointer = 0;
				while(nums[pointer] != max || !seenMax) {
					if(nums[pointer] == max) {
						seenMax = true;
					}
					pointer ++;
				}
				l = pointer;
				r = pointer;
			}
			else {
				int[] pfx = new int[n];
				int[] sfx = new int[n];
				for(int i = 0; i < n; i++) {
					pfx[i] = nums[i];
					if(i != 0) {
						pfx[i] = Math.max(pfx[i], pfx[i - 1]);
					}
				}
				for(int i = n - 1; i >= 0; i--) {
					sfx[i] = nums[i];
					if(i != n - 1) {
						sfx[i] = Math.max(sfx[i], sfx[i + 1]);
					}
				}
				int min = Integer.MAX_VALUE;
				while(nums[l] != max) {
					l ++;
				}
				while(nums[r] != max) {
					r --;
				}
				for(int i = l; i <= r; i++) {
					min = Math.min(min, nums[i]);
				}
				isValid = false;
				while(true) {
					//System.out.println(l + " " + r + " " + pfx[l - 1] + " " + sfx[r + 1] + " " + min);
					if(l == 0 || r == n - 1) {
						break;
					}
					if(pfx[l - 1] == sfx[r + 1] && min == pfx[l - 1]) {
						isValid = true;
						break;
					}
					//expansion cases.
					if(l > 1 && r < n - 2) {
						//System.out.println(Math.min(pfx[l - 2], Math.min(sfx[r + 1], Math.min(min, nums[l - 1]))) + " " + Math.min(pfx[l - 1], Math.min(sfx[r + 2], Math.min(min, nums[r + 1]))));
						if(Math.min(pfx[l - 2], Math.min(sfx[r + 1], Math.min(min, nums[l - 1]))) > Math.min(pfx[l - 1], Math.min(sfx[r + 2], Math.min(min, nums[r + 1])))) {	//left expansion ends up with greater value
							l --;
							min = Math.min(min, nums[l]);
							//System.out.println("LEFT");
						}
						else {
							r ++;
							min = Math.min(min, nums[r]);
							//System.out.println("RIGHT");
						}
					}
					else if(l > 1) {	//expand to left
						l --;
						min = Math.min(min, nums[l]);
					}
					else if(r < n - 2) {	//expand to right
						r ++;
						min = Math.min(min, nums[r]);
					}
					else {	//can't expand any more
						break;
					}
				}
			}
			if(isValid) {
				fout.append("YES\n");
				fout.append(l).append(" ").append(r - l + 1).append(" ").append(n - r - 1);
				fout.append("\n");
			}
			else {
				fout.append("NO\n");
			}
		}
		System.out.print(fout);
	}
}
