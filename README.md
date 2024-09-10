# BluePromise

BluePromise implements the Promise pattern for Unreal's Blueprints, allowing users to implement and manage asynchronous logic in Blueprint easily. Similar to Unity's coroutines.

The biggest advantage Blue Promise has is a more manageable Latent Action behavior. You get to decide whether a new Blue Promise should cancel the old one or not.

## How to Install

Clone the repository into your project's Plugins folder and build the project.

## Differences from Latent Actions

BluePromise gives the user more control by allowing the user to cancel any BluePromise. This makes managing multiple concurrent asynchronous flows much easier.

## The Anatomy of a Blue Promise

![image](https://github.com/user-attachments/assets/2626b92c-d568-4583-95bd-c991639f39d5)

1. You can optionally attach a Promise Context to the Context pin as an easy way to cancel the promise later.
2. The "Async Action" return value can be used to cancel the Promise directly.
3. The "then" pin above "On Continue" can be used to spawn multiple Promises in a non-blocking way.

In pseudocode, the above would be similar to:
```cpp
WaitForSeconds(1.0)
.OnComplete([]()
{
  // Run when WaitForSeconds ends (after one second).
})
.OnCancel([]()
{
  // Run when WaitForSeconds is canceled.
})
```

## Examples

Nested event loop for an enemy AI: (Note that the Wait Loop node needs to be manually continued with nodes like Continue After Delay)
![image](https://github.com/user-attachments/assets/9c527462-3ed0-4c66-a085-6d1ccef91bc1)
