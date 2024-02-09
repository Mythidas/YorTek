#include "Generated/EngineImport.h"
#include "NativeComponent.h"

void Yor::Import::ImportComponents(ApplicationDomain* domain)
{
  auto rigidbody = ComponentFactory<Scripts::NativeComponent>()
    .data<&Scripts::NativeComponent::rb>("RB", offsetof(Scripts::NativeComponent, rb))
    .data<&Scripts::NativeComponent::importCount>("ImportCount", offsetof(Scripts::NativeComponent, importCount))
    .Register(domain);
}
