module Main(main) where
 
import qualified Data.ByteString.Char8 as B
import Data.Int (Int64)
import Control.Monad(replicateM)
import Data.Functor
import Data.List
import Data.Array
import Data.Maybe

-- Codeforces - 2000A

-- ok, so iterating through strings to check stuff is very annoying. 
 
getNums :: B.ByteString -> [Int]
getNums =
    let
        f1 = (map ((fst.fromJust) . B.readInt))
        f2 = (B.split ' ')
    in f1.f2

readInts :: IO [Int]
readInts = getNums <$> B.getLine

is_val1 :: String -> Bool
is_val1 s = length(s) >= 3 && (take 2 s) == "10" && not (length(s) == 3 && (drop 2 s) == "1")

is_val2 :: String -> Bool
is_val2 s = take 1 (drop 2 s) /= "0"

solve :: Int -> IO ()
solve t = do
    s <- getLine
    if is_val1(s) && is_val2(s) then putStrLn "YES"
    else putStrLn "NO"

    if t /= 1 then solve(t - 1)
    else return ()

main :: IO ()
main = do
    input <- ((map fromIntegral <$> readInts) :: IO [Int])
    let [t] = input
    solve(t)



    