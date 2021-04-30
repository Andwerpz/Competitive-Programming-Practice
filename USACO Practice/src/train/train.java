//package train;

import java.util.*;
import java.io.*;

public class train {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		ArrayList<Integer> times = new ArrayList<Integer>();
		boolean goingLeft = true;
		if(fin.readLine().equals("to tail")) {
			goingLeft = false;
		}
		if(k == 1) {
			//System.out.println("CJEC");
			goingLeft = true;
		}
		if(k == n) {
			goingLeft = false;
		}
		char[] s = fin.readLine().toCharArray();
		char prev = '0';
		times.add(0);
		for(int i = 0; i < s.length; i++) {
			char next = s[i];
			if(next != prev) {
				times.add(0);
				prev = next;
			}
			times.set(times.size() - 1, times.get(times.size() - 1) + 1);
		}
		int curTime = 0;
		boolean stowawayWin = true;
		int ans = 0;
		for(int i = 0; i < times.size(); i++) {
			//System.out.println("time segment: " + times.get(i));
			if(i % 2 == 0) {	//the train is moving
				////System.out.println(i);
				boolean goodCase = false;
				int timeNeeded = times.get(i);
				int timeRemaining = 0;
				if(i == 0) {	//special case since we can't control where the stowaway starts
					if(goingLeft && m > k || !goingLeft && m < k) {
						goodCase = true;
					}
					else {
						timeRemaining = goingLeft? (k - 1) : (n - k);
					}
				}
				if(i != 0 || goodCase){
					timeRemaining = goingLeft? (k - 1 + n - 1) : (n - k + n - 1);
				}
				if(timeNeeded >= timeRemaining) {
					//System.out.println(k - 1 + n - 1 + " " + (n - k + n - 1) + " " + goingLeft);
					ans += timeRemaining;
					stowawayWin = false;
					break;
				}
				else {
					ans += timeNeeded;
				}
				//TODO update controller position, just do a for loop
				for(int j = 0; j < timeNeeded; j++) {
					if(k == 1 || k == n) {
						goingLeft = !goingLeft;
					}
					k += goingLeft? -1 : 1;
					//System.out.println(k);
				}
			}
			else {	//train is stopped
				int timeNeeded = times.get(i);
				for(int j = 0; j < timeNeeded; j++) {
					if(k == 1 || k == n) {
						goingLeft = !goingLeft;
					}
					k += goingLeft? -1 : 1;
					//System.out.println(k + " " + goingLeft);
				}
				ans += timeNeeded;
			}
		}
		if(stowawayWin) {
			System.out.println("Stowaway");
		}
		else {
			System.out.println("Controller " + ans);
		}
	}
}
