module Main(main) where
 
import qualified Data.ByteString.Char8 as B
import Data.Int (Int64)
import Control.Monad(replicateM)
import Data.Functor
import Data.List
import Data.Array
import Data.Maybe

-- Codeforces - 4A

-- first time using haskell, this stuff is jank
 
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
    input <- ((map fromIntegral <$> readInts) :: IO [Int64])
    let [w] = input
    if w > 2 && w `mod` 2 == 0 then putStrLn "YES"
    else putStrLn "NO"