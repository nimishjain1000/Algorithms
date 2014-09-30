import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class Solution {
	//https://www.hackerrank.com/challenges/gem-stones
	
public static void findCommonElement(String[] array){
		int count_common_element=0;
		int array_size=array.length;
		List<String> list_elements_of_first_rock=listOfSingleElementInARock(array[0]);
		for (String element_of_1_rock : list_elements_of_first_rock) {
			int check_common=1;
			for(int i=1;i<array_size;i++){  
				List<String> list_elements_of_i_rock=listOfSingleElementInARock(array[i]);
				if(list_elements_of_i_rock.contains(element_of_1_rock)){
						check_common++;
					}
				}
			if(array_size!=1 && check_common==array_size){
				count_common_element++;
			}
		}	
		System.out.println(count_common_element-1);
	}
	public static void toStringList(List<String> list){
		System.out.println("");
		for (String string : list) {
			System.out.print(string);
		}
	}
	public static List<String> listOfSingleElementInARock(String rock){
		List<String> list_element=new ArrayList<String>();
		String[] list_elements_of_rock=rock.split("");
		for (String element_contain : list_elements_of_rock) {
			if(!list_element.contains(element_contain)){
				list_element.add(element_contain);
			}
		}
		return list_element;
	}
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
       int s = in.nextInt();
          String[] ar = new String[s];
		    for(int i=0;i<s;i++){
		       ar[i]=in.next(); 
		    }
			 findCommonElement(ar);
	}
}