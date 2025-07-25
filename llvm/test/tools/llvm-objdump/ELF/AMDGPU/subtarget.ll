define amdgpu_kernel void @test_kernel() {
  ret void
}

; Test subtarget detection. Disassembly is only supported for GFX8 and beyond.
;
; ----------------------------------GFX12--------------------------------------
;
; RUN: llc -mtriple=amdgcn-amd-amdhsa --amdhsa-code-object-version=6 -mcpu=gfx12-generic -filetype=obj -O0 -o %t.o %s
; RUN: llvm-objdump -D --arch-name=amdgcn -mllvm --amdhsa-code-object-version=6 --mcpu=gfx12-generic %t.o > %t-specify.txt
; RUN: llvm-objdump -D -mllvm --amdhsa-code-object-version=6 %t.o > %t-detect.txt
; RUN: diff %t-specify.txt %t-detect.txt
;
; RUN: llc -mtriple=amdgcn-amd-amdhsa -mcpu=gfx1201 -filetype=obj -O0 -o %t.o %s
; RUN: llvm-objdump -D --arch-name=amdgcn --mcpu=gfx1201 %t.o > %t-specify.txt
; RUN: llvm-objdump -D %t.o > %t-detect.txt
; RUN: diff %t-specify.txt %t-detect.txt
;
; RUN: llc -mtriple=amdgcn-amd-amdhsa -mcpu=gfx1200 -filetype=obj -O0 -o %t.o %s
; RUN: llvm-objdump -D --arch-name=amdgcn --mcpu=gfx1200 %t.o > %t-specify.txt
; RUN: llvm-objdump -D %t.o > %t-detect.txt
; RUN: diff %t-specify.txt %t-detect.txt

; RUN: llc -mtriple=amdgcn-amd-amdhsa -mcpu=gfx1250 -filetype=obj -O0 -o %t.o %s
; RUN: llvm-objdump -D --arch-name=amdgcn --mcpu=gfx1250 %t.o > %t-specify.txt
; RUN: llvm-objdump -D %t.o > %t-detect.txt
; RUN: diff %t-specify.txt %t-detect.txt

; ----------------------------------GFX11--------------------------------------
;
; RUN: llc -mtriple=amdgcn-amd-amdhsa --amdhsa-code-object-version=6 -mcpu=gfx11-generic -filetype=obj -O0 -o %t.o %s
; RUN: llvm-objdump -D --arch-name=amdgcn -mllvm --amdhsa-code-object-version=6 --mcpu=gfx11-generic %t.o > %t-specify.txt
; RUN: llvm-objdump -D -mllvm --amdhsa-code-object-version=6 %t.o > %t-detect.txt
; RUN: diff %t-specify.txt %t-detect.txt

; RUN: llc -mtriple=amdgcn-amd-amdhsa -mcpu=gfx1153 -filetype=obj -O0 -o %t.o %s
; RUN: llvm-objdump -D --arch-name=amdgcn --mcpu=gfx1153 %t.o > %t-specify.txt
; RUN: llvm-objdump -D %t.o > %t-detect.txt
; RUN: diff %t-specify.txt %t-detect.txt

; RUN: llc -mtriple=amdgcn-amd-amdhsa -mcpu=gfx1152 -filetype=obj -O0 -o %t.o %s
; RUN: llvm-objdump -D --arch-name=amdgcn --mcpu=gfx1152 %t.o > %t-specify.txt
; RUN: llvm-objdump -D %t.o > %t-detect.txt
; RUN: diff %t-specify.txt %t-detect.txt

; RUN: llc -mtriple=amdgcn-amd-amdhsa -mcpu=gfx1151 -filetype=obj -O0 -o %t.o %s
; RUN: llvm-objdump -D --arch-name=amdgcn --mcpu=gfx1151 %t.o > %t-specify.txt
; RUN: llvm-objdump -D %t.o > %t-detect.txt
; RUN: diff %t-specify.txt %t-detect.txt

; RUN: llc -mtriple=amdgcn-amd-amdhsa -mcpu=gfx1150 -filetype=obj -O0 -o %t.o %s
; RUN: llvm-objdump -D --arch-name=amdgcn --mcpu=gfx1150 %t.o > %t-specify.txt
; RUN: llvm-objdump -D %t.o > %t-detect.txt
; RUN: diff %t-specify.txt %t-detect.txt

; RUN: llc -mtriple=amdgcn-amd-amdhsa -mcpu=gfx1103 -filetype=obj -O0 -o %t.o %s
; RUN: llvm-objdump -D --arch-name=amdgcn --mcpu=gfx1103 %t.o > %t-specify.txt
; RUN: llvm-objdump -D %t.o > %t-detect.txt
; RUN: diff %t-specify.txt %t-detect.txt

; RUN: llc -mtriple=amdgcn-amd-amdhsa -mcpu=gfx1102 -filetype=obj -O0 -o %t.o %s
; RUN: llvm-objdump -D --arch-name=amdgcn --mcpu=gfx1102 %t.o > %t-specify.txt
; RUN: llvm-objdump -D %t.o > %t-detect.txt
; RUN: diff %t-specify.txt %t-detect.txt

; RUN: llc -mtriple=amdgcn-amd-amdhsa -mcpu=gfx1101 -filetype=obj -O0 -o %t.o %s
; RUN: llvm-objdump -D --arch-name=amdgcn --mcpu=gfx1101 %t.o > %t-specify.txt
; RUN: llvm-objdump -D %t.o > %t-detect.txt
; RUN: diff %t-specify.txt %t-detect.txt

; RUN: llc -mtriple=amdgcn-amd-amdhsa -mcpu=gfx1100 -filetype=obj -O0 -o %t.o %s
; RUN: llvm-objdump -D --arch-name=amdgcn --mcpu=gfx1100 %t.o > %t-specify.txt
; RUN: llvm-objdump -D %t.o > %t-detect.txt
; RUN: diff %t-specify.txt %t-detect.txt

; ----------------------------------GFX10--------------------------------------
; RUN: llc -mtriple=amdgcn-amd-amdhsa --amdhsa-code-object-version=6 -mcpu=gfx10-3-generic -filetype=obj -O0 -o %t.o %s
; RUN: llvm-objdump -D --arch-name=amdgcn -mllvm --amdhsa-code-object-version=6 --mcpu=gfx10-3-generic %t.o > %t-specify.txt
; RUN: llvm-objdump -D  -mllvm --amdhsa-code-object-version=6 %t.o > %t-detect.txt
; RUN: diff %t-specify.txt %t-detect.txt

; RUN: llc -mtriple=amdgcn-amd-amdhsa -mcpu=gfx1036 -filetype=obj -O0 -o %t.o %s
; RUN: llvm-objdump -D --arch-name=amdgcn --mcpu=gfx1036 %t.o > %t-specify.txt
; RUN: llvm-objdump -D %t.o > %t-detect.txt
; RUN: diff %t-specify.txt %t-detect.txt

; RUN: llc -mtriple=amdgcn-amd-amdhsa -mcpu=gfx1035 -filetype=obj -O0 -o %t.o %s
; RUN: llvm-objdump -D --arch-name=amdgcn --mcpu=gfx1035 %t.o > %t-specify.txt
; RUN: llvm-objdump -D %t.o > %t-detect.txt
; RUN: diff %t-specify.txt %t-detect.txt

; RUN: llc -mtriple=amdgcn-amd-amdhsa -mcpu=gfx1034 -filetype=obj -O0 -o %t.o %s
; RUN: llvm-objdump -D --arch-name=amdgcn --mcpu=gfx1034 %t.o > %t-specify.txt
; RUN: llvm-objdump -D %t.o > %t-detect.txt
; RUN: diff %t-specify.txt %t-detect.txt

; RUN: llc -mtriple=amdgcn-amd-amdhsa -mcpu=gfx1033 -filetype=obj -O0 -o %t.o %s
; RUN: llvm-objdump -D --arch-name=amdgcn --mcpu=gfx1033 %t.o > %t-specify.txt
; RUN: llvm-objdump -D %t.o > %t-detect.txt
; RUN: diff %t-specify.txt %t-detect.txt

; RUN: llc -mtriple=amdgcn-amd-amdhsa -mcpu=gfx1032 -filetype=obj -O0 -o %t.o %s
; RUN: llvm-objdump -D --arch-name=amdgcn --mcpu=gfx1032 %t.o > %t-specify.txt
; RUN: llvm-objdump -D %t.o > %t-detect.txt
; RUN: diff %t-specify.txt %t-detect.txt

; RUN: llc -mtriple=amdgcn-amd-amdhsa -mcpu=gfx1031 -filetype=obj -O0 -o %t.o %s
; RUN: llvm-objdump -D --arch-name=amdgcn --mcpu=gfx1031 %t.o > %t-specify.txt
; RUN: llvm-objdump -D %t.o > %t-detect.txt
; RUN: diff %t-specify.txt %t-detect.txt

; RUN: llc -mtriple=amdgcn-amd-amdhsa -mcpu=gfx1030 -filetype=obj -O0 -o %t.o %s
; RUN: llvm-objdump -D --arch-name=amdgcn --mcpu=gfx1030 %t.o > %t-specify.txt
; RUN: llvm-objdump -D %t.o > %t-detect.txt
; RUN: diff %t-specify.txt %t-detect.txt

; RUN: llc -mtriple=amdgcn-amd-amdhsa --amdhsa-code-object-version=6 -mcpu=gfx10-1-generic -filetype=obj -O0 -o %t.o %s
; RUN: llvm-objdump -D --arch-name=amdgcn -mllvm --amdhsa-code-object-version=6 --mcpu=gfx10-1-generic %t.o > %t-specify.txt
; RUN: llvm-objdump -D  -mllvm --amdhsa-code-object-version=6 %t.o > %t-detect.txt
; RUN: diff %t-specify.txt %t-detect.txt

; RUN: llc -mtriple=amdgcn-amd-amdhsa -mcpu=gfx1013 -filetype=obj -O0 -o %t.o %s
; RUN: llvm-objdump -D --arch-name=amdgcn --mcpu=gfx1013 %t.o > %t-specify.txt
; RUN: llvm-objdump -D %t.o > %t-detect.txt
; RUN: diff %t-specify.txt %t-detect.txt

; RUN: llc -mtriple=amdgcn-amd-amdhsa -mcpu=gfx1012 -filetype=obj -O0 -o %t.o %s
; RUN: llvm-objdump -D --arch-name=amdgcn --mcpu=gfx1012 %t.o > %t-specify.txt
; RUN: llvm-objdump -D %t.o > %t-detect.txt
; RUN: diff %t-specify.txt %t-detect.txt

; RUN: llc -mtriple=amdgcn-amd-amdhsa -mcpu=gfx1011 -filetype=obj -O0 -o %t.o %s
; RUN: llvm-objdump -D --arch-name=amdgcn --mcpu=gfx1011 %t.o > %t-specify.txt
; RUN: llvm-objdump -D %t.o > %t-detect.txt
; RUN: diff %t-specify.txt %t-detect.txt

; RUN: llc -mtriple=amdgcn-amd-amdhsa -mcpu=gfx1010 -filetype=obj -O0 -o %t.o %s
; RUN: llvm-objdump -D --arch-name=amdgcn --mcpu=gfx1010 %t.o > %t-specify.txt
; RUN: llvm-objdump -D %t.o > %t-detect.txt
; RUN: diff %t-specify.txt %t-detect.txt


; ----------------------------------GFX9---------------------------------------
;
; RUN: llc -mtriple=amdgcn-amd-amdhsa --amdhsa-code-object-version=6 -mcpu=gfx9-4-generic -filetype=obj -O0 -o %t.o %s
; RUN: llvm-objdump -D --arch-name=amdgcn -mllvm --amdhsa-code-object-version=6 --mcpu=gfx9-4-generic %t.o > %t-specify.txt
; RUN: llvm-objdump -D  -mllvm --amdhsa-code-object-version=6 %t.o > %t-detect.txt
; RUN: diff %t-specify.txt %t-detect.txt

; RUN: llc -mtriple=amdgcn-amd-amdhsa --amdhsa-code-object-version=6 -mcpu=gfx9-generic -filetype=obj -O0 -o %t.o %s
; RUN: llvm-objdump -D --arch-name=amdgcn -mllvm --amdhsa-code-object-version=6 --mcpu=gfx9-generic %t.o > %t-specify.txt
; RUN: llvm-objdump -D  -mllvm --amdhsa-code-object-version=6 %t.o > %t-detect.txt
; RUN: diff %t-specify.txt %t-detect.txt

; RUN: llc -mtriple=amdgcn-amd-amdhsa -mcpu=gfx950 -filetype=obj -O0 -o %t.o %s
; RUN: llvm-objdump -D --arch-name=amdgcn --mcpu=gfx950 %t.o > %t-specify.txt
; RUN: llvm-objdump -D %t.o > %t-detect.txt
; RUN: diff %t-specify.txt %t-detect.txt

; RUN: llc -mtriple=amdgcn-amd-amdhsa -mcpu=gfx942 -filetype=obj -O0 -o %t.o %s
; RUN: llvm-objdump -D --arch-name=amdgcn --mcpu=gfx942 %t.o > %t-specify.txt
; RUN: llvm-objdump -D %t.o > %t-detect.txt
; RUN: diff %t-specify.txt %t-detect.txt

; RUN: llc -mtriple=amdgcn-amd-amdhsa -mcpu=gfx90c -filetype=obj -O0 -o %t.o %s
; RUN: llvm-objdump -D --arch-name=amdgcn --mcpu=gfx90c %t.o > %t-specify.txt
; RUN: llvm-objdump -D %t.o > %t-detect.txt
; RUN: diff %t-specify.txt %t-detect.txt

; RUN: llc -mtriple=amdgcn-amd-amdhsa -mcpu=gfx90a -filetype=obj -O0 -o %t.o %s
; RUN: llvm-objdump -D --arch-name=amdgcn --mcpu=gfx90a %t.o > %t-specify.txt
; RUN: llvm-objdump -D %t.o > %t-detect.txt
; RUN: diff %t-specify.txt %t-detect.txt

; RUN: llc -mtriple=amdgcn-amd-amdhsa -mcpu=gfx909 -filetype=obj -O0 -o %t.o %s
; RUN: llvm-objdump -D --arch-name=amdgcn --mcpu=gfx909 %t.o > %t-specify.txt
; RUN: llvm-objdump -D %t.o > %t-detect.txt
; RUN: diff %t-specify.txt %t-detect.txt

; RUN: llc -mtriple=amdgcn-amd-amdhsa -mcpu=gfx908 -filetype=obj -O0 -o %t.o %s
; RUN: llvm-objdump -D --arch-name=amdgcn --mcpu=gfx908 %t.o > %t-specify.txt
; RUN: llvm-objdump -D %t.o > %t-detect.txt
; RUN: diff %t-specify.txt %t-detect.txt

; RUN: llc -mtriple=amdgcn-amd-amdhsa -mcpu=gfx906 -filetype=obj -O0 -o %t.o %s
; RUN: llvm-objdump -D --arch-name=amdgcn --mcpu=gfx906 %t.o > %t-specify.txt
; RUN: llvm-objdump -D %t.o > %t-detect.txt
; RUN: diff %t-specify.txt %t-detect.txt

; RUN: llc -mtriple=amdgcn-amd-amdhsa -mcpu=gfx904 -filetype=obj -O0 -o %t.o %s
; RUN: llvm-objdump -D --arch-name=amdgcn --mcpu=gfx904 %t.o > %t-specify.txt
; RUN: llvm-objdump -D %t.o > %t-detect.txt
; RUN: diff %t-specify.txt %t-detect.txt

; RUN: llc -mtriple=amdgcn-amd-amdhsa -mcpu=gfx902 -filetype=obj -O0 -o %t.o %s
; RUN: llvm-objdump -D --arch-name=amdgcn --mcpu=gfx902 %t.o > %t-specify.txt
; RUN: llvm-objdump -D %t.o > %t-detect.txt
; RUN: diff %t-specify.txt %t-detect.txt

; RUN: llc -mtriple=amdgcn-amd-amdhsa -mcpu=gfx900 -filetype=obj -O0 -o %t.o %s
; RUN: llvm-objdump -D --arch-name=amdgcn --mcpu=gfx900 %t.o > %t-specify.txt
; RUN: llvm-objdump -D %t.o > %t-detect.txt
; RUN: diff %t-specify.txt %t-detect.txt


; ----------------------------------GFX8---------------------------------------
;
; RUN: llc -mtriple=amdgcn-amd-amdhsa -mcpu=gfx810 -filetype=obj -O0 -o %t.o %s
; RUN: llvm-objdump -D --arch-name=amdgcn --mcpu=gfx810 %t.o > %t-specify.txt
; RUN: llvm-objdump -D %t.o > %t-detect.txt
; RUN: diff %t-specify.txt %t-detect.txt

; RUN: llc -mtriple=amdgcn-amd-amdhsa -mcpu=gfx803 -filetype=obj -O0 -o %t.o %s
; RUN: llvm-objdump -D --arch-name=amdgcn --mcpu=gfx803 %t.o > %t-specify.txt
; RUN: llvm-objdump -D %t.o > %t-detect.txt
; RUN: diff %t-specify.txt %t-detect.txt

; RUN: llc -mtriple=amdgcn-amd-amdhsa -mcpu=gfx802 -filetype=obj -O0 -o %t.o %s
; RUN: llvm-objdump -D --arch-name=amdgcn --mcpu=gfx802 %t.o > %t-specify.txt
; RUN: llvm-objdump -D %t.o > %t-detect.txt
; RUN: diff %t-specify.txt %t-detect.txt

; RUN: llc -mtriple=amdgcn-amd-amdhsa -mcpu=gfx801 -filetype=obj -O0 -o %t.o %s
; RUN: llvm-objdump -D --arch-name=amdgcn --mcpu=gfx801 %t.o > %t-specify.txt
; RUN: llvm-objdump -D %t.o > %t-detect.txt
; RUN: diff %t-specify.txt %t-detect.txt
