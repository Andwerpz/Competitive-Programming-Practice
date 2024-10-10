module Main(main) where
 
import qualified Data.ByteString.Char8 as B
import Data.Int (Int64)
import Control.Monad(replicateM)
import Data.Functor
import Data.List
import Data.Array
import Data.Maybe

//Codeforces - 2010B

//bruh
 
getNums :: B.ByteString -> [Int]
getNums =
    let
        f1 = (map ((fst.fromJust) . B.readInt))
        f2 = (B.split ' ')
    in f1.f2

readInts :: IO [Int]
readInts = getNums <$> B.getLine

main :: IO ()
main = do
    input <- ((map fromIntegral <$> readInts) :: IO [Int])
    let [a, b] = input
    if min a b == 2 then print(1)
    else if max a b == 2 then print(3)
    else print(2)
    