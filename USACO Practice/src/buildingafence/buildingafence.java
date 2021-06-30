//package buildingafence;

import java.util.*;
import java.io.*;

public class buildingafence {
	public static void main(String[] args) throws IOException {
		
		//all we have to do is go from step to step, and generate for each step where the next fence could possibly cover. 
		//using the possible locations of the next fence, we once again generate the next fences possible locations.
		//once we reach the end, we see if the possible locations mesh with the last fence. If they do, then it is a valid input,
		//otherwise, invalid input.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int k = Integer.parseInt(st.nextToken());
			st = new StringTokenizer(fin.readLine());
			int[] ground = new int[n];
			for(int i = 0; i < n; i++) {
				ground[i] = Integer.parseInt(st.nextToken());
			}
			int high = ground[0] + k - 1;
			int low = ground[0];
			boolean isValid = true;
			//System.out.println(low + " " + high);
			for(int i = 1; i < n - 1; i++) {
				int nextGround = ground[i];
				if(high < nextGround) {	//the next ground level is above the possible highest fence
					isValid = false;
					break;
				}
				else if(nextGround <= high && nextGround >= low) {	//next ground level is in between the high and low ranges of the prev possible fence
					low = nextGround;
					high = Math.min(high + k - 1, nextGround + 2 * k - 2);
				}
				else {	//next ground level is below the low bound of the prev possible fence
					if(low > nextGround + 2 * k - 2) {	//the next level can't reach this levels lower bound
						isValid = false;
						break;
					}
					else if(low <= nextGround + k - 1) {
						low = nextGround;
						high = nextGround + 2 * k - 2;
					}
					else {	//the next level can reach the prev levels lower bound
						high = nextGround + 2 * k - 2;
						low = low - (k - 1);
					}
				}
				//System.out.println(low + " " + high + " STEP: " + i);
			}
			int lastLow = ground[n - 1];
			int lastHigh = ground[n - 1] + k - 1;
			//System.out.println("LAST CHECK: " + lastLow + " " + lastHigh);
			if((high >= lastLow && high <= lastHigh || low >= lastLow && low <= lastHigh || high >= lastLow && high >= lastHigh && low <= lastLow && low <= lastHigh) && isValid) {
				fout.append("YES");
			}
			else {
				fout.append("NO");
			}
			////System.out.println("END OF TESTCASE");
			fout.append("\n");
		}
		System.out.print(fout);
	}
}
