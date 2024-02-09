#include "Generated/EngineImport.h"
#include "YTEngine/Physics/Rigidbody.h"

void Yor::Import::ImportComponents(ApplicationDomain* domain)
{
  auto rigidbody = ComponentFactory<Physics::Rigidbody>()
    .data<&Physics::Rigidbody::X>("X", offsetof(Physics::Rigidbody, X))
    .data<&Physics::Rigidbody::Y>("Y", offsetof(Physics::Rigidbody, Y))
    .Register(domain);
}
