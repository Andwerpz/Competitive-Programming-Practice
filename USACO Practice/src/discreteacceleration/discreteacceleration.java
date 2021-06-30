//package discreteacceleration;

import java.util.*;
import java.io.*;

public class discreteacceleration {
	public static void main(String[] args) throws IOException {
		
		//1408C
		
		//this solution is based off of the fact that the two cars will meet either in between two flags, or at a flag. 
		//first, construct a dictionary storing for each flag, what time the car reaches it. If both cars reach a flag at the same time, then that's
		//the answer.
		//else, iterate down the times array. If you see for two adjacent flags that one car arrived at the first flag before the other car left the second flag, and the first car
		//left after the second car arrived, then you know that the cars met in this segment. 
		
		//now that you have the cars speeds, their times of entry and the distance between them, it is trivial to calculate their time of meeting.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int l = Integer.parseInt(st.nextToken());
			double[] flags = new double[n];
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				flags[i] = Integer.parseInt(st.nextToken());
			}
			double[][] times = new double[2][n + 2];	//0 for the car starting at 0, 1 for the car starting at l.
			for(int i = 0; i < n + 1; i++) {
				if(i == 0) {
					times[0][1] = flags[0];
					times[1][n] = l - flags[n - 1];
				}
				else if(i < n){
					times[0][i + 1] = times[0][i] + (flags[i] - flags[i - 1]) / (double) (i + 1);
					times[1][n - i] = times[1][n - i + 1] + (flags[n - i] - flags[n - i - 1]) / (double) (i + 1);
				}
				else {
					times[0][n + 1] = times[0][n] + (l - flags[n - 1]) / (double) (i + 1);
					times[1][0] = times[1][1] + (flags[0]) / (double) (i + 1);
				}
			}
//			System.out.println();
//			for(double[] i : times) {
//				for(double j : i) {
//					System.out.print(j + " ");
//				}
//				System.out.println();
//			}
//			System.out.println();
//			for(double i : flags) {
//				System.out.print(i + " ");
//			}
			//System.out.println();
			//System.out.println();
			double ans = 0;
			for(int i = 0; i < times[0].length - 1; i++) {
				if(times[0][i] <= times[1][i] && times[0][i + 1] >= times[1][i + 1]) {
					//System.out.println(times[0][i] + " " + times[0][i + 1]);
					//System.out.println(times[1][i] + " " + times[1][i + 1]);
					double aSpeed = i + 1;
					double bSpeed = n - (i - 1);
					double initDist = 0;
					double initTime = 0;
					boolean aFirst = false;
					if(times[0][i] <= times[1][i + 1]) {
						double diff = times[1][i + 1] - times[0][i];
						initDist = diff * aSpeed;
						initTime = diff;
						aFirst = true;
					}
					else {
						double diff = times[0][i] - times[1][i + 1];
						initDist = diff * bSpeed;
						initTime = diff;
					}
					double dist = 0;
					double ratio = aSpeed / (aSpeed + bSpeed);
					if(i == 0) {
						dist = flags[0];
					}
					else if(i == n) {
						dist = l - flags[n - 1];
					}
					else {
						dist = flags[i] - flags[i - 1];
					}
//					System.out.println("INITDIST: " + initDist);
//					System.out.println("DIST: " + dist);
//					System.out.println("ASPEED: " + aSpeed);
//					System.out.println("BSPEED: " + bSpeed);
//					System.out.println("I: " + i);
//					System.out.println("RATIO: " + ratio);
					dist -= initDist;
					double time = (dist * ratio) / aSpeed;
					//System.out.println("TIME: " + time);
					ans = (aFirst? times[1][i + 1] : times[0][i]) + time;
					break;
				}
			}
			for(int i = 0; i < times[0].length; i++) {
				if(times[0][i] == times[1][i]) {
					ans = times[0][i];
					break;
				}
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
