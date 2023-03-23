import openai

openai.api_key = "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"

model_engine = "text-davinci-003"

while True:
  prompt = input("Input: ")

  completion = openai.Completion.create(
   engine=model_engine,
   prompt=prompt,
   max_tokens=1024,
   n=1,
   stop=None,
   temperature=0.5,
  )

  print(completion['choices'][0]['text'])
