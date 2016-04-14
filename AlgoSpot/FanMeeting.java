import java.util.BitSet;
import java.util.Scanner;


public class FanMeeting
{
    private static BitSet makeBits(String sex)
    {
        BitSet bitSet = new BitSet(sex.length());
        
        for(int i = 0; i < sex.length(); ++i)
        {
            bitSet.set(i, sex.charAt(i) == 'M');
        }
        
        return bitSet;
    }
    
    public static void main(String[] args)
    {
        Scanner in = new Scanner(System.in);
        int caseCount = Integer.parseInt(in.nextLine());
        
        while( --caseCount >= 0 )
        {
            int allHug = 0;
            
            String lineText = in.nextLine();
            BitSet member = makeBits(lineText);
            int memberCnt = lineText.length();
            
            lineText = in.nextLine();
            BitSet fan = makeBits(lineText);
            int fanCnt = lineText.length();
            
            int loopCnt = fanCnt - memberCnt + 1;
            for(int i = 0; i < loopCnt; ++i)
            {
                BitSet union = fan.get(fanCnt - memberCnt - i, fanCnt - i);
                
                if( !union.intersects(member) )
                    allHug += 1;
            }
            
            System.out.println(allHug);
        }
    }
}
