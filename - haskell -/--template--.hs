module Main(main) where
 
import qualified Data.ByteString.Char8 as B
import Data.Int (Int64)
import Control.Monad(replicateM)
import Data.Functor
import Data.List
import Data.Array
import Data.Maybe
 
getNums :: B.ByteString -> [Int]
getNums =
    let
        f1 = (map ((fst.fromJust) . B.readInt))
        f2 = (B.split ' ')
    in f1.f2

readInts :: IO [Int]
readInts = getNums <$> B.getLine

solve :: Int -> IO ()
solve t = do

    if t /= 1 then solve(t - 1)
    else return ()

main :: IO ()
main = do
    input <- ((map fromIntegral <$> readInts) :: IO [Int])
    let [t] = input
    solve(t)
    