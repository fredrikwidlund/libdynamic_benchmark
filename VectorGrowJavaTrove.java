import gnu.trove.list.array.TIntArrayList;

public class VectorGrowJavaTrove {
    public static void main(String args[]) {
        int i, j = 0, n = Integer.parseInt(args[0]);
        long[] m;
        long t;
        TIntArrayList v = new TIntArrayList();
        
        m = new long[101];
        t = System.nanoTime();
        m[0] = 0;
        try
            {
                for (i = 0; i < n; i += n / 100)
                    {
                        for (j = 0; j < n / 100; j ++)
                            {
                                v.add(j);
                            }
                        m[i / (n / 100) + 1] = System.nanoTime() - t;
                    }
            }
        catch (Exception e)
            {
                System.out.println("TIntArrayList add " + j);
                System.exit(-1);
            }
        
        System.out.println("\"size\",\"time\"");
        for (i = 0; i <= 100; i ++)
            System.out.printf("%d,%f\n", i * (n / 100), (float) m[i] / 1000000000f);
    }
}
