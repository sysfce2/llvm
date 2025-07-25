; RUN: llc -mtriple=amdgcn -mcpu=tahiti -start-before=amdgpu-unify-divergent-exit-nodes < %s | FileCheck -enable-var-scope -check-prefix=GCN %s
; RUN: llc -enable-no-signed-zeros-fp-math -mtriple=amdgcn -mcpu=tahiti -start-before=amdgpu-unify-divergent-exit-nodes < %s | FileCheck -enable-var-scope -check-prefix=GCN %s

; --------------------------------------------------------------------------------
; rcp_legacy tests
; --------------------------------------------------------------------------------

; GCN-LABEL: {{^}}v_fneg_rcp_legacy_f32:
; GCN: {{buffer|flat}}_load_dword [[A:v[0-9]+]]
; GCN: v_rcp_legacy_f32_e64 [[RESULT:v[0-9]+]], -[[A]]
; GCN: {{buffer|flat}}_store_dword [[RESULT]]
define amdgpu_kernel void @v_fneg_rcp_legacy_f32(ptr addrspace(1) %out, ptr addrspace(1) %a.ptr) #0 {
  %tid = call i32 @llvm.amdgcn.workitem.id.x()
  %tid.ext = sext i32 %tid to i64
  %a.gep = getelementptr inbounds float, ptr addrspace(1) %a.ptr, i64 %tid.ext
  %out.gep = getelementptr inbounds float, ptr addrspace(1) %out, i64 %tid.ext
  %a = load volatile float, ptr addrspace(1) %a.gep
  %rcp = call float @llvm.amdgcn.rcp.legacy(float %a)
  %fneg = fsub float -0.000000e+00, %rcp
  store float %fneg, ptr addrspace(1) %out.gep
  ret void
}

declare i32 @llvm.amdgcn.workitem.id.x() #1
declare float @llvm.amdgcn.rcp.legacy(float) #1

attributes #0 = { nounwind }
attributes #1 = { nounwind readnone }
