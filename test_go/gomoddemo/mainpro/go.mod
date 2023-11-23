module mainpro

go 1.21.0

require github.com/bytedance/sonic v1.10.2

require (
	github.com/chenzhuoyu/base64x v0.0.0-20230717121745-296ad89f973d // indirect
	github.com/chenzhuoyu/iasm v0.9.0 // indirect
	github.com/klauspost/cpuid/v2 v2.0.9 // indirect
	github.com/twitchyliquid64/golang-asm v0.15.1 // indirect
	golang.org/x/arch v0.0.0-20210923205945-b76863e36670 // indirect
)

require othermod1 v0.0.0

replace othermod1 => /mnt/d/WorkSpace/3github/ElegantTest/test_go/gomoddemo/mainpro/otherMod

require utilxx v0.0.1

replace utilxx => /mnt/d/WorkSpace/3github/ElegantTest/test_go/gomoddemo/otherpro
