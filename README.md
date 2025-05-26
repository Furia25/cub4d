```mermaid
---
config:
  theme: redux
  look: classic
  layout: dagre
---
flowchart TD
 subgraph Triple_Buffering["Triple_Buffering"]
    direction LR
        Buffer1["Game Buffer"]
        Buffer2["Write buffer"]
        Buffer3["Read buffer"]
  end
    n1["CUBE 3d <br>"] -- Launch --> GameThread["Game Thread"]
    n1 -- Launch Main --> GraphicsThread["Graphics Thread"]
    Buffer1 -- Replace --> Buffer2
    Buffer2 <-- Exchange New --> Buffer3
    Buffer3 L_Buffer3_GraphicsThread_0@== Process ==> GraphicsThread
    GameThread -- Execute --> n2["Game Logic <br>"]
    n2 L_n2_Triple_Buffering_0@-- Update --> Triple_Buffering
    n1@{ shape: terminal}
    style n1 fill:#FFCDD2
    style GameThread fill:#f9f,stroke:#333,stroke-width:2px
    style GraphicsThread fill:#f9f,stroke:#333,stroke-width:2px
    style n2 fill:#BBDEFB
    linkStyle 0 stroke:#757575,fill:none
    linkStyle 1 stroke:#757575,fill:none
    L_Buffer3_GraphicsThread_0@{ animation: fast } 
    L_n2_Triple_Buffering_0@{ animation: fast }

```
