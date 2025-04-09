import Development.Shake
import Development.Shake.FilePath

buildDir :: FilePath
buildDir = "_build"

main :: IO ()
main = shakeArgs shakeOptions { shakeFiles = buildDir } $ do
    want [buildDir </> "VirtMaxU"]

    buildDir </> "*.o" %> \out -> do
        let src = dropDirectory1 $ out -<.> "c"
        need [src]
        cmd_ "gcc" ["-std=c23", "-c", src, "-o", out]

    buildDir </> "VirtMaxU" %> \out -> do
        let obj = buildDir </> "main.o"
        need [obj]
        cmd_ "gcc" [obj, "-o", out]

    phony "clean" $ do
        liftIO $ putStrLn "Cleaning build directory..."
        removeFilesAfter buildDir ["//*"]
